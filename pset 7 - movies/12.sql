-- * list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.*

SELECT title FROM movies WHERE id IN
-- *Find all movies title from movies table

(SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper')
-- *Find the movie_id that Bradley Cooper starred*

INTERSECT
-- *Operator that return common record between 2 movie_id that include Bradley Cooper and Jennifer Lawrence

SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence'));
-- *Find the movie_id that Jennifer Lawrence starred*
