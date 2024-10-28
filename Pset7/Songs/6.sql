SELECT s.name
FROM songs s
INNER JOIN artists a ON a.id = s.artist_id
WHERE (a.name = "Post Malone")
