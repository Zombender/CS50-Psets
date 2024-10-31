import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, valid_password

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]
    user_history = db.execute('''SELECT id_user, symbol, name, SUM(shares)
                              FROM logs
                              WHERE id_user=?
                              GROUP BY symbol
                              HAVING SUM(shares) > 0
                              ORDER BY price DESC''',user_id)

    current_usar_cash = db.execute("SELECT * FROM user WHERE id = ?",user_id)
    current_price = 0
    for stock in user_history:
        stock_s = lookup(stock["symbol"])
        stock["symbol_price"] = stock_s["price"]
        stock["total"] = stock_s["price"] * stock["SUM(shares)"]
        current_price+=stock["total"]

    return render_template("index.html",user_history=user_history,
                           current_user_cash=current_usar_cash,
                           current_price=current_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method != "POST": return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if symbol == "":
        return apology("Missing symbol",400)
    if shares == "" or shares.isalpha():
        return apology("Missing shares",400)
    if '-' in shares or '.' in shares:
        return apology("Only integers",400)

    symbol_s = lookup(symbol)
    if not symbol_s:
        return apology("Symbol not found",400)

    shares = int(shares)
    total = shares * symbol_s["price"]
    user_id = session["user_id"]
    current_user_cash = db.execute("SELECT * FROM user WHERE id = ?",user_id)
    if current_user_cash[0]["cash"] < total:
        return apology("Can't afford",400)

    db.execute('''INSERT INTO logs (id_user,symbol,name,shares,price)
               VALUES (?,?,?,?,?)''',user_id,symbol_s["symbol"],symbol_s["name"],
               shares,symbol_s["price"])
    cash = current_user_cash[0]["cash"]
    db.execute("UPDATE user SET cash = ? WHERE id = ?",cash-total,user_id)
    flash('Bought!')
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_history = db.execute('''SELECT id_user, symbol, shares, price, transaction_date
    FROM logs
    WHERE id_user = ?
    ORDER BY transaction_date''',session["user_id"])
    return render_template("history.html",user_history=user_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM user WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method !='POST':
        return render_template("quote.html")

    symbol = request.form.get("symbol")
    if symbol == '':
        return apology("Input is empty",400)
    stock_s = lookup(symbol)
    if not stock_s:
        return apology("Invalid symbol",400)
    return render_template("quoted.html",stock_s=stock_s)


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()
    if request.method != "POST": return render_template("register.html")

    user = request.form.get("username")
    password = request.form.get("password")
    confirmation_password = request.form.get("confirmation")

    fetch = db.execute("SELECT * FROM user WHERE username = ?",user)

    if len(fetch) >=1:
        return apology("user already exist",400)

    valid = valid_password(password)
    if valid is not True:
        return apology(valid,400)
    if not password == confirmation_password:
        return apology("Confirmation does not match",400)

    if password == "" or confirmation_password == "" or user == "":
        return apology("User information incomplete,400")

    hashcode = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
    db.execute("INSERT INTO user (username, hash) VALUES(?, ?)", user, hashcode)

    return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares fof stock"""
    user_id = session["user_id"]
    user_history = db.execute('''SELECT id_user, symbol, name, SUM(shares)
                              FROM logs
                              WHERE id_user=?
                              GROUP BY symbol
                              HAVING SUM(shares) > 0
                              ORDER BY price DESC''',user_id)
    if request.method != "POST":
         return render_template("sell.html",user_history=user_history)

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if symbol == None:
        return apology("Missing symbol",400)

    if shares == None or shares.isalpha():
        return apology("Missing shares",400)

    if '-' in shares or '.' in shares:
        return apology("Only integers",400)

    if int(shares) == 0:
        return apology("Shares can't be zero.",400)
    symbol_s = lookup(symbol)

    if not symbol_s:
        return apology("Symbol not found",400)

    cash = db.execute("SELECT * FROM user WHERE id = ?",user_id)[0]["cash"]

    if user_history[0]["SUM(shares)"] < int(shares):
        return apology("Too many shares",400)
    total = symbol_s["price"] * int(shares)


    if cash < total:
        return apology("Can't afford",400)


    db.execute("UPDATE user SET cash = ? WHERE id = ?",cash+total,user_id)

    db.execute('''INSERT INTO logs (id_user,symbol,name,shares,price)
               VALUES (?,?,?,?,?)''',user_id,symbol_s["symbol"],symbol_s["name"],
               -int(shares),symbol_s["price"])
    flash('Sold!')
    return redirect("/")




