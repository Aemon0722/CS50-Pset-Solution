-- * list the names of all people
SELECT DISTINCT(name) FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004))
-- *who starred in a movie released in 2004*
ORDER BY birth;
-- * ordered by birth year.*
