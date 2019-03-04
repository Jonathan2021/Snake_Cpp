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
#include	<ncurses.h>
#include	<memory>

/*
 * =====================================================================================
 *        Class:  Food
 *  Description: Food the snake eats 
 *
 * =====================================================================================
 */


enum Type{
    food,
    wall,
    snake,
    nothing
};

enum Color{
    red,
    blue,
    black,
    white,
    yellow,
    green,
    pink
};

/*
 * =====================================================================================
 *        Class:  Something
 *  Description: virtual base class for all objects on map  
 * =====================================================================================
 */

class Arena;

class Something
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Something (const Type type, const Color color, const bool deadly, std::pair<unsigned, unsigned> coords);                             /* constructor */

        /* ====================  ACCESSORS     ======================================= */
        Type& type(void);
        Color& color(void);
        std::pair<unsigned, unsigned>& coords(void);
        bool& deadly(void);
        /* ====================  MUTATORS      ======================================= */
        virtual char print(void) = 0;
        virtual void trigger(Arena& arena) = 0;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        Type type_;
        Color color_;
        bool deadly_;
        std::pair<unsigned, unsigned> coords_;
}; /* -----  end of class Something  ----- */


class Food : public Something
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Food (const unsigned i, const Color color, const bool deadly, const std::pair<unsigned, unsigned> coords);
        virtual ~Food (void);                            /* destructor       */
        /* ====================  ACCESSORS     ======================================= */
            int increase(void) const;
        /* ====================  MUTATORS      ======================================= */
            virtual char print(void) override;
            void trigger(Arena& arena) override;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    private:
        int increase_;
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
        Banana (const unsigned y, const unsigned x);
        Banana (const std::pair<unsigned, unsigned> coords);/* constructor      */
        ~Banana (void);                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        /* ====================  MUTATORS      ======================================= */
        char print(void) override;
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
        Mushroom (const unsigned y, const unsigned x);
        Mushroom (const std::pair<unsigned, unsigned> coords);/* constructor      */
        ~Mushroom (void);                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        char print(void) override;
        /* ====================  OPERATORS     ======================================= */


        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int mushroom_count;
}; /* -----  end of class Mushroom  ----- */


/*
 * =====================================================================================
 *        Class:  LifeUp
 *  Description:  
 * =====================================================================================
 */
class LifeUp : public Food
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        LifeUp (const unsigned y, const unsigned x);
        LifeUp (const std::pair<unsigned, unsigned> coords);/* constructor */
        ~LifeUp (void);
        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        char print(void) override;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int life_count;
}; /* -----  end of class LifeUp  ----- */


/*
 * =====================================================================================
 *        Class:  Snake
 *  Description:  main character of the game
 *
 * =====================================================================================
 */

class Snake : public Something
{
    public:

        /* ====================  LIFECYCLE     ======================================= */
        Snake (unsigned y, unsigned x);                             /* constructor      */
        Snake (std::pair<unsigned, unsigned> coords);
        ~Snake (void);                            /* destructor       */

        /* ====================  ACCESSORS     ======================================= */
        int size(void) const;
        /* ====================  MUTATORS      ======================================= */
        char print(void) override;
        void trigger(Arena& arena) override;
       /* ====================  OPERATORS     ======================================= */


        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int snake_count;
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
        std::shared_ptr<Snake> build(void) const;
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        std::shared_ptr<Snake> snake;

}; /* -----  end of class SnakeBuilder  ----- */


/*
 * =====================================================================================
 *        Class:  Wall
 *  Description:  wall element
 * =====================================================================================
 */
class Wall : public Something
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Wall (const unsigned y, const unsigned x);
        Wall (std::pair<unsigned, unsigned> coords);/* constructor */

        /* ====================  ACCESSORS     ======================================= */
        char print(void) override;
        void trigger(Arena& arena) override;
        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        static int wall_count;

}; /* -----  end of class Wall  ----- */


/*
 * =====================================================================================
 *        Class:  Player
 *  Description:  information about the player
 * =====================================================================================
 */

class Player
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Player (std::string name);                             /* constructor */

        /* ====================  ACCESSORS     ======================================= */
        std::string& name(void);
        unsigned& score(void); 
        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        std::string& name_;
        unsigned score_;
}; /* -----  end of class Player  ----- */


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
        Arena(const unsigned height, const unsigned width);                           /* constructor */
        /* ====================  ACCESSORS     ======================================= */
        Snake& head(void);
        unsigned& width(void);
        unsigned& height(void);
        unsigned& lives(void);
        int& direction(void); 
        std::vector<std::shared_ptr<Something>>& food(void);
        std::vector<std::shared_ptr<Something>>& snake(void);
        std::vector<std::shared_ptr<Something>>& wall(void);
        std::weak_ptr<Something>**& map(void);
        int& difficulty(void);
        int& growth(void);
        Player& player(void);
        WINDOW*& window(void);
        /* ====================  MUTATORS      ======================================= */
        bool in_bound(const std::pair<unsigned, unsigned> coords) const;
        bool in_bound(const unsigned y, const unsigned x) const;
        std::weak_ptr<Something>& get_pos(const unsigned y, const unsigned x);
        std::weak_ptr<Something>& get_pos(std::pair<unsigned, unsigned> pos);
        void new_direction(int key);
        void display(void) const;
        void init(void);
        void update(void);
        void add_something(std::shared_ptr<Something> something);
        void remove_something(std::shared_ptr<Something> something, int nb);
        void add_to_window(unsigned y, unsigned x, char c);
        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        unsigned height_;
        unsigned width_;
        unsigned lives_;
        int direction_;
        std::vector<std::shared_ptr<Something>> snake_;
        std::vector<std::shared_ptr<Something>> food_;
        std::vector<std::shared_ptr<Something>> wall_;
        std::weak_ptr<Something>** map_;
        int difficulty_;
        int growth_;
        Player player_;
        WINDOW* window_;
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
        ArenaBuilder();
        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */
        Arena build(void) const;
        ArenaBuilder& set_size(const unsigned height, const unsigned width);
        ArenaBuilder& set_player(std::string name);
        ArenaBuilder& set_difficulty(int p);

        /* ====================  OPERATORS     ======================================= */

        /* ====================  DATA MEMBERS  ======================================= */
    protected:

    private:
        Arena arena;

}; /* -----  end of class ArenaBuilder  ----- */

