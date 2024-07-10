SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);
-- *Find the average rating of movie released in 2012 from ratings table
