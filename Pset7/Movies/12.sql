SELECT title
FROM movies m
INNER JOIN stars s ON s.movie_id = m.id
INNER JOIN people p ON s.person_id = p.id
WHERE p.name IN ("Bradley Cooper", "Jennifer Lawrence")
GROUP BY title
HAVING COUNT(DISTINCT p.name) = 2;
