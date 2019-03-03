/*
 * =====================================================================================
 *
 *       Filename:  snake.cc
 *
 *    Description:  Implementation of classes
 *
 *        Version:  1.0
 *        Created:  14/02/2019 13:56:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Sands (js), jonathan.sands@epita.fr
 *        Company:  none
 *
 * =====================================================================================
 */


#include	<iostream>
#include	<assert.h>
#include	<ncurses.h>
#include	<climits>
#include	<stdexcept>
#include	<ncurses.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<memory>
#include	"snake.hh"



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Something
 *      Method:  Something
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Something::Something (const Type type, const Color color, const bool deadly, std::pair<unsigned, unsigned> coords)
    :type_(type)
    ,color_(color)
    ,deadly_(deadly)
    ,coords_(coords)
{
}  /* -----  end of method Something::Something  (constructor)  ----- */

Type& Something::type(void)
{
  return type_; 
}

Color& Something::color(void)
{
    return color_;
}

std::pair<unsigned, unsigned>& Something::coords(void)
{
    return coords_;
}

bool& Something::deadly(void)
{
    return deadly_;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Snake
 *      Method:  Snake
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Snake::Snake (unsigned y, unsigned x)
    :Something(snake, blue, true, std::make_pair(y, x))
{ snake_count++; }  /* -----  end of method Snake::Snake  (constructor)  ----- */

Snake::Snake (std::pair<unsigned, unsigned> coords)
    :Something(snake, blue, true, coords)
{ snake_count++; }


Snake::~Snake()
{ snake_count--; }

int Snake::size(void) const
{
    return snake_count;
}

char Snake::print(void)
{
    return 'S';
}

int Snake::snake_count = 0;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Food
 *      Method:  Food
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Food::Food (const unsigned i, const Color color, const bool deadly, const std::pair<unsigned, unsigned> coords)
    :Something(food, color, deadly, coords)
    ,increase_(i)
{
    food_count++;
}  /* -----  end of method Food::Food  (constructor)  ----- */

Food::~Food(void)
{
    food_count--;
}

int Food::increase(void) const
{
    return this->increase_;
}

char Food::print(void)
{
    return 'F';
}

int Food::food_count = 0;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Banana
 *      Method:  Banana
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Banana::Banana (const unsigned y, const unsigned x)
    :Food(3, yellow, false, std::make_pair(y, x))
{
    std::cout << "Created a Banana" << '\n';
    banana_count++;
}  /* -----  end of method Banana::Banana  (constructor)  ----- */

Banana::Banana (const std::pair<unsigned, unsigned> coords)
    :Food(3, yellow, false, coords)
{
    std::cout << "Created a Banana" << '\n';
    banana_count++;
}

Banana::~Banana(void)
{
    banana_count--;
}

char Banana::print (void)
{
    return 'B';
}

int Banana::banana_count = 0;

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mushroom
 *      Method:  Mushroom
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Mushroom::Mushroom (const unsigned y, const unsigned x)
    :Food(-3, red, true, std::make_pair(y, x))
{
    std::cout<< "Created a Mushroom" << '\n'; 
    mushroom_count++;
} /* -----  end of method Mushroom::Mushroom  (constructor)  ----- */

Mushroom::Mushroom (const std::pair<unsigned, unsigned> coords)
    :Food(-3, red, true, coords)
{
    std::cout<< "Created a Mushroom" << '\n'; 
    mushroom_count++;
}

Mushroom::~Mushroom (void)
{
    mushroom_count--;
}

char Mushroom::print(void)
{
    return 'M';
}

int Mushroom::mushroom_count = 0;


/*
 *--------------------------------------------------------------------------------------
 *       Class:  LifeUp
 *      Method:  LifeUp
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */

LifeUp::LifeUp (const unsigned y, const unsigned x)
    :Food(0, green, false, std::make_pair(y, x))
{
    life_count++;
}

LifeUp::LifeUp (std::pair<unsigned, unsigned> coords)
    :Food(0, green, false, coords)
{
    life_count++;
}  /* -----  end of method LifeUp::LifeUp  (constructor)  ----- */

LifeUp::~LifeUp (void)
{
    life_count--;
}

char LifeUp::print(void)
{
    return 'L';
}

int LifeUp::life_count = 0;

std::shared_ptr<Snake> SnakeBuilder::build(void) const
{
    return this->snake;
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  ArenaBuilder
 *      Method:  ArenaBuilder
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
ArenaBuilder::ArenaBuilder()
    :arena(Arena(0,0))
{}

Arena ArenaBuilder::build(void) const
{
    return this->arena;
}

ArenaBuilder& ArenaBuilder::set_size(const unsigned height, const unsigned width)
{
    arena.width() = width;
    arena.height() = height;
    return *this;
}

ArenaBuilder& ArenaBuilder::set_difficulty(int p)
{
    arena.difficulty() = p;
    return *this;
}

ArenaBuilder& ArenaBuilder::set_player(std::string name)
{
    arena.player().name() = name;
    return *this;
}



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Arena
 *      Method:  Arena
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Arena::Arena (const unsigned height, const unsigned  width)
    :height_(height)
    ,width_(width)
    ,direction_(0)
    ,snake_(std::vector<std::shared_ptr<Something>>{})
    ,food_(std::vector<std::shared_ptr<Something>>{})
    ,wall_(std::vector<std::shared_ptr<Something>>{})
    ,map_(nullptr)
    ,difficulty_(0)
    ,growth_(0)
    ,player_(Player(""))
{
}  /* -----  end of method Arena::Arena  (constructor)  ----- */

unsigned& Arena::width(void)
{
    return width_;
}

unsigned& Arena::height(void)
{
    return height_;
}

Snake& Arena::head(void)
{
    return *(std::dynamic_pointer_cast<Snake>(this->snake_.at(0)));
}

std::vector<std::shared_ptr<Something>>& Arena::food(void)
{
    return this->food_;
}

std::vector<std::shared_ptr<Something>>& Arena::snake(void)
{
    return this->snake_;
}

std::vector<std::shared_ptr<Something>>& Arena::wall(void)
{
    return this->wall_;
}

std::weak_ptr<Something>**& Arena::map(void)
{
    return this->map_;
}

int& Arena::difficulty()
{
    return this->difficulty_;
}

int& Arena::direction(void)
{
    return direction_;
}

unsigned& Arena::lives(void)
{
    return this->lives_;
}

int& Arena::growth(void)
{
    return this->growth_;
}

WINDOW*& Arena::window(void)
{
    return window_;
}

bool Arena::in_bound(const unsigned y, const unsigned x) const
{
    return (y < height_ && x < width_);
}

bool Arena::in_bound(const std::pair<unsigned, unsigned> pos) const
{
    return (pos.first < height_ && pos.second < width_);
}

std::weak_ptr<Something>& Arena::get_pos(const unsigned y, const unsigned x)
{
    return map_[y][x];
}

std::weak_ptr<Something>& Arena::get_pos(std::pair<unsigned, unsigned> pos)
{
    return map_[pos.first][pos.second];
}

void Arena::new_direction(int key)
{
    if (key == direction_ || key != KEY_UP || key != KEY_DOWN || key != KEY_LEFT || key != KEY_RIGHT)
        return;
    if ((key == KEY_DOWN && direction_ != KEY_UP) || (key == KEY_UP && direction_ != KEY_DOWN) || \
        (key == KEY_LEFT && direction_ != KEY_RIGHT) || (key == KEY_RIGHT && direction_ != KEY_LEFT))
    {
        direction_ = key;
    }
}

void Arena::display(void) const
{
    std::cout << "Arena display to be implemented \n";
}

void Arena::add_to_window(unsigned y, unsigned x, char c)
{
    mvwaddch(window_, y, x, c);
}


std::vector<std::shared_ptr<Something>>& get_vect(Arena& arena, std::shared_ptr<Something> something)
{
    Type type = something->type();
    if (type == food)
    {
        return arena.food();
    }
    else if (type == wall)
    {
        return arena.wall();
    }
    else if (type == snake)
    {
        return arena.snake();
    }
    else
        throw std::logic_error("Trying to add something with wrong type");
}

void add_something_to_window(Arena& arena, std::shared_ptr<Something> something)
{
    arena.add_to_window(something->coords().first, something->coords().second, something->print());
}

void Arena::add_something(std::shared_ptr<Something> something)
{
    auto& vect = get_vect(*this, something); 
    vect.push_back(something);
    add_something_to_window(*this, something);
}

void my_erase(std::vector<std::shared_ptr<Something>>& vect, std::shared_ptr<Something> element, int nb, Arena& arena)
{
    for (auto it = vect.begin(); it != vect.end(); ++it)
    {
        if(*it == element)
        {
            std::pair<unsigned, unsigned> pos;
            for (auto tmp = it; tmp != it + nb; ++tmp)
            {
                pos = (*tmp)->coords();
                arena.add_to_window(pos.first, pos.second, ' ');
            }
            vect.erase(it, it + nb);
            break;
        }
    }
}

void Arena::remove_something(std::shared_ptr<Something> something, int nb)
{
    auto vect = get_vect(*this, something);
    my_erase(vect, something, nb, *this);
}

void Arena::init(void)
{
    window_ = newwin(height_, width_, 0, 0);
    lives_ = 3 - difficulty_;
    map_ = new std::weak_ptr<Something>*[height_];
    for (unsigned i = 0; i < height_; ++i)
        map_[i] = new std::weak_ptr<Something>[width_]();
    if (snake_.empty())
    {
        add_something(std::make_shared<Snake>(height_ / 2 , width_ / 2));
        growth_ = 2;
    }
    unsigned y_temp;
    unsigned x_temp;
    for (auto i = 0; i < 4;)
    {
        y_temp = rand() % height_;
        x_temp = rand() % width_;
        if (!get_pos(y_temp, x_temp).expired())
            continue;
        if (i < difficulty_)
            add_something(std::make_shared<Mushroom>(y_temp, x_temp));
        else
            add_something(std::make_shared<Banana>(y_temp, x_temp));
        ++i;
    }
}

std::pair<unsigned, unsigned> ahead(Arena& arena)
{
    auto cur = arena.head().coords();
    int dir = arena.direction();
    if (dir == KEY_UP)
        cur.first -= 1;
    if (dir == KEY_DOWN)
        cur.first += 1;
    if (dir == KEY_LEFT)
        cur.second -= 1;
    if (dir == KEY_RIGHT)
        cur.second += 1;
    return cur;
}

void Arena::update(void)
{
    auto pos = ahead(*this);
    auto element = get_pos(pos);
    if (!element.expired())
    {
        element.lock()->trigger(*this);
    }
    if(growth_ > 0)
    {
        add_something(std::make_shared<Snake>(pos));
        growth_--;
        return;
    }
    else if (growth_ < 0)
    {
        remove_something(snake_.back(), 1);
        growth_++;
    }
    remove_something(snake_.back(), 1);
}

Player& Arena::player(void)
{
    return player_;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Wall
 *      Method:  Wall
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Wall::Wall (const unsigned y, const unsigned x)
    :Something(wall, white, true, std::make_pair(y, x))
{
}  /* -----  end of method Wall::Wall  (constructor)  ----- */

Wall::Wall (std::pair<unsigned, unsigned> coords)
    :Something(wall, white, true, coords)
{
}  /* -----  end of method Wall::Wall  (constructor)  ----- */

char Wall::print(void)
{
    return 'W';
}

int Wall::wall_count = 0;



/*
 *--------------------------------------------------------------------------------------
 *       Class:  Player
 *      Method:  Player
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Player::Player (std::string name)
    :name_(name)
    ,score_(0)
{
}  /* -----  end of method Player::Player  (constructor)  ----- */

std::string& Player::name(void)
{
    return this->name_;
}

unsigned& Player::score(void)
{
    return this->score_;
}



void Snake::trigger(Arena& arena)
{
    auto& snake = arena.snake();
    for(auto i = snake.begin(); i != snake.end(); ++i)
    {
        if (&**i == this)
        {
            for (auto it = i + 1; it != snake.end(); ++it)
            {
                arena.add_something(std::make_shared<Wall>((*it)->coords()));
            }
            snake.erase(i, snake.end());
            break;
        }    
    }
    arena.lives()--;
}

void Food::trigger(Arena& arena)
{
    auto& food = arena.food();
    for (auto it = food.begin(); it != food.end(); ++it)
    {
        if (&**it == this)
        {
            arena.growth() += (std::dynamic_pointer_cast<Food>(*it))->increase();
            break;
        }
    }
}

void Wall::trigger(Arena& arena)
{
    //auto coords = arena.snake().front()->coords();
    arena.snake().erase(arena.snake().begin());
    arena.lives()--;
}

