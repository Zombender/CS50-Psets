from cs50 import get_string

def get_text_grade(text:str)->int:
    letters = 0
    words = 0
    sentences = 0
    for char in text:
        if char.isalpha():
            letters+=1
        elif char == ' ':
            words+=1
        elif char == '.' or char == '!' or char == '?':
            sentences+=1
    words+=1
    L = letters/words*100
    S = sentences/words*100
    grade = 0.0588*L-0.296*S-15.8
    return grade

text = get_string("Text: ")
grade = get_text_grade(text)
if grade <=0:
    print("Before Grade 1")
elif grade >16:
    print("Grade 16+")
else:
    print(f"Grade {round(grade)}")
