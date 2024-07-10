-- *list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.*

SELECT title FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE id IN
-- *Find the title by combining movies table and rating tables with the movie_id*

(SELECT movie_id FROM stars WHERE person_id =
-- *Find the movid_id where 'Chadwick Boseman' starred in*

(SELECT id FROM people WHERE name = 'Chadwick Boseman'))
-- *Find the person_id of 'Chadwick Boseman'*

ORDER BY rating DESC LIMIT 5;
-- *Order the 5 highest rating movies*
