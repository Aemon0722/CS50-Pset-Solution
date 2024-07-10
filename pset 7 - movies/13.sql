-- *list the names of all people who starred in a movie in which Kevin Bacon also starred*

SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
-- *Find the all people person_id who work with Kevin Bacon

(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958)))
-- *Find movies in which the correct Kevin Bacon also starred*

AND id != (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958);
-- *Exclude Kevin Bacon himself into the list*

