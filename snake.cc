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
#include	<climits>
#include	<stdexcept>
#include	<curses.h>
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

void Something::print(void)
{
    std::cout << "Something, deadly? " << std::boolalpha << deadly_ << '\n';
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

void Snake::print(void)
{
    std::cout << "I'm a snake\n";
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

void Food::print(void)
{
    std::cout << "Food of type : " << type() <<  \
        ", I increase by : " << increase_ << ", am I deadly ? " << \
        std::boolalpha << deadly() << '\n';
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

void Banana::print (void)
{
    std::cout << "I'm a banana, the fact that i'm deadly is " << std::boolalpha << deadly() <<\
        " and I increase your size by " << increase() << '\n';
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

void Mushroom::print(void)
{
 std::cout << "I'm a banana, the fact that i'm deadly is " << std::boolalpha << deadly() <<\
        " and I increase your size by " << increase() << '\n';
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

void LifeUp::print(void)
{
    std::cout << "I'm a life-up !\n";
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
    ,snake_(std::vector<std::shared_ptr<Snake>>{})
    ,food_(std::vector<std::shared_ptr<Food>>{})
    ,wall_(std::vector<std::shared_ptr<Wall>>{})
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
    return *(this->snake_.at(0));
}

std::vector<std::shared_ptr<Food>>& Arena::food(void)
{
    return this->food_;
}

std::vector<std::shared_ptr<Snake>>& Arena::snake(void)
{
    return this->snake_;
}

std::vector<std::shared_ptr<Wall>>& Arena::wall(void)
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

unsigned& Arena::lives(void)
{
    return this->lives_;
}

int& Arena::growth(void)
{
    return this->growth_;
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

void Arena::display(void) const
{
    std::cout << "Arena display to be implemented \n";
}

void Arena::add_something(std::shared_ptr<Something> something)
{
    Type type = something->type();
    if (type == ::food)
    {
        food_.push_back(std::dynamic_pointer_cast<Food>(something));
    }
    else if (type == ::wall)
    {
        wall_.push_back(std::dynamic_pointer_cast<Wall>(something));
    }
    else if (type == ::snake)
    {
        snake_.push_back(std::dynamic_pointer_cast<Snake>(something));
    }
    else
        throw std::logic_error("Trying to add something with wrong type");
    get_pos(something->coords()) = something;
}

void Arena::init(void)
{
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
        if (get_pos(y_temp, x_temp).expired())
            continue;
        if (i < difficulty_)
            add_something(std::make_shared<Mushroom>(y_temp, x_temp));
        else
            add_something(std::make_shared<Banana>(y_temp, x_temp));
        ++i;
    }
}

void Arena::update(void)
{
    std::cout << "To be implemented\n";
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

void Wall::print(void)
{
    std::cout << "I'm a wall !\n";
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
            arena.growth() += (*it)->increase();
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

