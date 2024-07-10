SELECT title, rating FROM movies JOIN ratings ON movies.id = ratings.movie_id
-- *Combining movie title and rating from movies and ratings table*
WHERE year = 2010 ORDER BY rating DESC, title ASC;
-- the movie selected were released in 2010 in a desecending order by rating, then by title in alphabetical order
