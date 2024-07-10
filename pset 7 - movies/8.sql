SELECT name FROM people WHERE id IN
-- *find name from people table who play Toy Story
(SELECT person_id FROM stars WHERE movie_id =
-- *find the person_id that has involved in Toy Story from stars table*
(SELECT id FROM movies WHERE title = 'Toy Story')
-- *find the id of Toy Story from movies table*
);
