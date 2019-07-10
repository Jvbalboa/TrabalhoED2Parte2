#include "Rating.h"

Rating::Rating()
{
    userID = -1;
    movieID = -1;
}

Rating::Rating(int user, int movie)
{
    userID = user;
    movieID = movie;
}

Rating::~Rating()
{
    //dtor
}

int Rating::getUserID()
{
    return userID;
}

int Rating::getMovieID()
{
    return movieID;
}

void Rating::setUserID(int id)
{
    userID = id;
}

void Rating::setMovieID(int id)
{
    movieID = id;
}
