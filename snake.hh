/*
 * =====================================================================================
 *
 *       Filename:  snake.hh
 *
 *    Description:  Class and struct definitions of all objects in the game
 *
 *        Version:  1.0
 *        Created:  14/02/2019 13:26:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Sands (js), jonathan.sands@epita.fr
 *        Company:  none
 *
 * =====================================================================================
 */

#pragma once

#include	<iostream>
#include	<vector>

#define ARENA_SIZE 80

/*
 * =====================================================================================
 *        Class:  Food
 *  Description: Food the snake eats 
 *
 * =====================================================================================
 */
class Food
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Food (const char t, const std::string c, const unsigned i, const bool d, unsigned y, unsigned x);                             /* constructor      */
        virtual ~Food ();                            /* destructor       */
        /* ====================  ACCESSORS     ======================================= */
            char type() const;
            std::string& color();
            unsigned increase() const;
            bool deadly() const;
            std::pair<unsigned, unsigned>& coords();
        /* ====================  MUTATORS      ======================================= */
            virtual void print() const;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    private:
        char type_;
        std::string color_;
        int increase_;
        bool deadly_;
        std::pair<unsigned, unsigned> coords_;
        static int food_count;
}; /* -----  end of class Food  ----- */




/*
 * =====================================================================================
 *        Class:  Banana
 *  Description:  good food
 *  
 * =====================================================================================
 */
class Banana : public Food
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Banana (const unsigned y, const unsigned x);                             /* constructor      */
        ~Banana ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        /* ====================  MUTATORS      ======================================= */
        void print() const override;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int banana_count;
}; /* -----  end of class Banana  ----- */



/*
 * =====================================================================================
 *        Class:  Mushroom
 *  Description:  bad food
 *
 * =====================================================================================
 */
class Mushroom : public Food
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Mushroom (const unsigned y, const unsigned x);                             /* constructor      */
        ~Mushroom ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        void print() const override;
        /* ====================  OPERATORS     ======================================= */


        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int mushroom_count;
}; /* -----  end of class Mushroom  ----- */

/*
 * =====================================================================================
 *        Class:  Snake
 *  Description:  main character of the game
 *
 * =====================================================================================
 */
class Snake
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Snake ();                             /* constructor      */
        ~Snake ();                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        unsigned& size();
        std::string& color();
        unsigned& lives();
        char& direction();
        std::string& name();
        /* ====================  MUTATORS      ======================================= */
        unsigned score() const;
        void print() const;
        std::pair<unsigned, unsigned> head() const;
       /* ====================  OPERATORS     ======================================= */


        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        std::string color_;
        std::string name_;
        unsigned size_;
        char direction_;
        unsigned lives_;
        std::vector<std::pair<unsigned, unsigned>> body_;
}; /* -----  end of class Snake  ----- */



/*
 * =====================================================================================
 *        Class:  SnakeBuilder
 *  Description:  Building snake
 *
 * =====================================================================================
 */
class SnakeBuilder
{
    public:
        /* ====================  LIFECYCLE     ======================================= */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
            Snake build() const;
            SnakeBuilder& set_color(const std::string color);
            SnakeBuilder& set_life(const unsigned life);
            SnakeBuilder& set_name(const std::string name);
            SnakeBuilder& set_size(const unsigned size);
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        Snake snake;

}; /* -----  end of class SnakeBuilder  ----- */



/*
 * =====================================================================================
 *        Class:  Arena
 *  Description:  Where everything happens
 *
 * =====================================================================================
 */
class Arena
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Arena(const unsigned s);                           /* constructor */
        /* ====================  ACCESSORS     ======================================= */
        Snake& snake();
        unsigned& size();
        std::vector<Food>& food();
        char** map() const;
        void set_snake(Snake* snake);
        void set_map(char** map);
        /* ====================  MUTATORS      ======================================= */
        bool in_bound() const;
        char& get_pos(const unsigned y, const unsigned x) const;
        char& get_pos(std::pair<const unsigned, const unsigned> pos) const;
        void display() const;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        unsigned size_;
        Snake* snake_;
        std::vector<Food> food_;
        char** map_;

}; /* -----  end of class Arena  ----- */



/*
 * =====================================================================================
 *        Class:  ArenaBuilder
 *  Description:  
 *
 * =====================================================================================
 */
class ArenaBuilder
{
    public:
        /* ====================  LIFECYCLE     ======================================= */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        Arena build() const;
        ArenaBuilder& set_snake(Snake* snake);
        ArenaBuilder& set_size(const unsigned size);
        ArenaBuilder& set_map(char** map);

        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        Arena arena;

}; /* -----  end of class ArenaBuilder  ----- */

