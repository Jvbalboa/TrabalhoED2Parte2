#ifndef RATING_H
#define RATING_H


class Rating
{
    private:
        int userID;
        int movieID;

    public:
        Rating();
        Rating(int user, int movie);
        virtual ~Rating();

        //gets e sets
        int getUserID();
        int getMovieID();
        void setUserID(int id);
        void setMovieID(int id);

    friend class NoB;
    friend class ArvoreB;
};

#endif // RATING_H
