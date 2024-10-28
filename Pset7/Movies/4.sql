SELECT COUNT(DISTINCT r.rating ==10.0)
AS "cantidad de peliculas"
FROM movies m
INNER JOIN ratings r ON m.id = r.movie_id
