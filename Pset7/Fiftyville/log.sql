-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE (month = 7 AND day = 28 AND year = 2023 AND street = 'Humphrey Street');

SELECT name,transcript
FROM interviews
WHERE(month = 7 AND day = 28 AND year = 2023
AND transcript LIKE '%bakery%')

--10:15 - Theft stole duck at this time

SELECT b.hour,b.minute,b.license_plate,p.name
FROM bakery_security_logs b
JOIN people p ON p.license_plate = b.license_plate
WHERE(b.month = 7 AND b.day = 28 AND b.year = 2023 AND b.hour = 10
AND b.minute BETWEEN 15 AND 25);

--Leggett Street/withdraw

SELECT DISTINCT at.account_number, p.name AS sender_name, ph.receiver, p_rec.name AS receiver_name, at.month, at.day
FROM atm_transactions at
INNER JOIN bank_accounts b ON b.account_number = at.account_number
INNER JOIN people p ON p.id = b.person_id
INNER JOIN phone_calls ph ON p.phone_number = ph.caller
INNER JOIN people p_rec ON ph.receiver = p_rec.phone_number
WHERE (at.month = 7 AND at.day = 28 AND at.year = 2023
       AND at.atm_location = 'Leggett Street'
       AND at.transaction_type = 'withdraw'
       AND ph.duration < 60);


--Suspects
/*
Kenny
Taylor
Bruce
Benista
Diana
*/

/*
flights - city = Fiftyville
*/
SELECT a.city AS 'Origin', a_d.city AS 'Destination',f.id
FROM flights f
INNER JOIN airports a ON f.origin_airport_id = a.id
INNER JOIN airports a_d ON f.destination_airport_id = a_d.id
WHERE(f.year = 2023 AND f.month = 7 AND f.day=29)
ORDER BY f.hour ASC
LIMIT 1; -- = They were to New York City


SELECT p.name, pa.seat
FROM passengers pa
INNER JOIN people p ON pa.passport_number = p.passport_number
INNER JOIN flights f ON f.id = pa.flight_id
WHERE flight_id = (
    SELECT f.id
    FROM flights f
    INNER JOIN airports a ON f.origin_airport_id = a.id
    INNER JOIN airports a_d ON f.destination_airport_id = a_d.id
    WHERE(f.year = 2023 AND f.month = 7 AND f.day=29)
    ORDER BY f.hour ASC
    LIMIT 1
);

SELECT p.name, pa.seat
FROM passengers pa
INNER JOIN flights f ON f.id = pa.flight_id
INNER JOIN people p ON pa.passport_number = p.passport_number
WHERE(f.id = 36)

--Thief = Robin

--Accomplice = Robin OR Charlotte
