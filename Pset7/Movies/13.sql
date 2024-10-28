SELECT DISTINCT p2.name
FROM stars s1
INNER JOIN people p1 ON s1.person_id = p1.id
INNER JOIN stars s2 ON s1.movie_id = s2.movie_id
INNER JOIN people p2 ON p2.id = s2.person_id
INNER JOIN MOVIES m ON m.id = s1.movie_id
WHERE p1.name = "Kevin Bacon"
AND p2.name <> "Kevin Bacon"

