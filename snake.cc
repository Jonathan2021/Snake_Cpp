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
#include	<climits>
#include	"snake.hh"


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Snake
 *      Method:  Snake
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Snake::Snake ()
    :color_("green")
    ,name_("Joe")
    ,size_(3)
    ,direction_(0)
    ,lives_(3)
    ,body_(std::vector<std::pair<unsigned, unsigned>>{})
{}  /* -----  end of method Snake::Snake  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Snake
 *      Method:  ~Snake
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Snake::~Snake ()
{
    body_.clear();
}  /* -----  end of method Snake::~Snake  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Snake
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */

unsigned& Snake::size()
{
    return this->size_;
}

std::string& Snake::color()
{
    return this->color_;
}

unsigned& Snake::lives()
{
    return this->lives_;
}

char& Snake::direction()
{
    return this->direction_;
}

unsigned Snake::score() const
{
    return (this->lives_ * this->size_);
}

std::string& Snake::name()
{
    return this->name_;
}

std::pair<unsigned, unsigned> Snake::head() const
{
    if(this->body_.size())
        return this->body_.at(0);
    return std::make_pair(UINT_MAX, UINT_MAX);
}

void Snake::print() const
{
    std::cout << "Snake " << name_ << " :\n";
    std::cout << "Color : " << color_ << '\n';
    std::cout << "Size: " << size_ << '\n';
    std::cout << "Lives left : " << lives_ << '\n';
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Food
 *      Method:  Food
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Food::Food (const char t, const std::string c, const unsigned i, const bool d,
        unsigned y, unsigned x)
    :type_(t)
    ,color_(c)
    ,increase_(i)
    ,deadly_(d)
    ,coords_(y, x)
{
    food_count++;
}  /* -----  end of method Food::Food  (constructor)  ----- */

Food::~Food()
{
    food_count--;
}

char Food::type() const
{
    return this->type_;
}

std::string& Food::color()
{
    return this->color_;
}

unsigned Food::increase() const
{
    return this->increase_;
}

bool Food::deadly() const
{
    return this->deadly_;
}

std::pair<unsigned, unsigned>& Food::coords()
{
    return coords_;
}

void Food::print() const
{
    std::cout << "Food of type : " << type_ << ", color : " << color_ << \
        ", I increase by : " << increase_ << ", am I deadly ? " << \
        std::boolalpha << deadly_ << '\n';
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
    :Food('B', "yellow", 2, false, y, x)
{
    std::cout << "Created a Banana" << '\n';
    banana_count++;
}  /* -----  end of method Banana::Banana  (constructor)  ----- */

Banana::~Banana()
{
    banana_count--;
}

void Banana::print () const
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
    :Food('M', "red", -2, false, y, x)
{
    std::cout<< "Created a Mushroom" << '\n'; 
    mushroom_count++;
} /* -----  end of method Mushroom::Mushroom  (constructor)  ----- */

Mushroom::~Mushroom ()
{
    mushroom_count--;
}

void Mushroom::print() const
{
 std::cout << "I'm a banana, the fact that i'm deadly is " << std::boolalpha << deadly() <<\
        " and I increase your size by " << increase() << '\n';
}

int Mushroom::mushroom_count = 0;

SnakeBuilder& SnakeBuilder::set_color(const std::string color)
{
    snake.color() = color;
    return *this;
}

SnakeBuilder& SnakeBuilder::set_life(const unsigned life)
{
    snake.lives() = life;
    return *this;
}

SnakeBuilder& SnakeBuilder::set_name(const std::string name)
{
    snake.name() = name;
    return *this;
}

SnakeBuilder& SnakeBuilder::set_size(const unsigned size)
{
    snake.size() = size;
    return *this;
}

Snake SnakeBuilder::build() const
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
Arena ArenaBuilder::build() const
{
    return this->arena;
}

ArenaBuilder& ArenaBuilder::set_snake(Snake* snake)
{
    arena.set_snake(snake);
    return *this;
}

ArenaBuilder& ArenaBuilder::set_size(const unsigned size)
{
    arena.size() = size;
    return *this;
}

ArenaBuilder& ArenaBuilder::set_map(char** map)
{
    arena.set_map(map);
    return *this;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Arena
 *      Method:  Arena
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Arena::Arena (const unsigned s)
    :size_((s < 100) ? s : 100)
    ,snake_(nullptr)
    ,food_(std::vector<Food>{})
    ,map_(nullptr)
{}  /* -----  end of method Arena::Arena  (constructor)  ----- */

Snake& Arena::snake()
{
    return *(this->snake_);
}

unsigned& Arena::size()
{
    return this->size_;
}

std::vector<Food>& Arena::food()
{
    return this->food_;
}

char** Arena::map() const
{
    return map_;
}

void Arena::set_snake(Snake* snake)
{
    this->snake_ = snake;
}

void Arena::set_map(char** map)
{
    this->map_ = map;
}

bool Arena::in_bound() const
{
    auto head = snake_->head();
    auto y = std::get<0>(head);
    auto x = std::get<1>(head);
    return (y < size_ && x < size_);
}

char& Arena::get_pos(const unsigned y, const unsigned x) const 
{
    return map_[y][x];
}

char& Arena::get_pos(std::pair<const unsigned, const unsigned> pos) const
{
    return map_[std::get<0>(pos)][std::get<1>(pos)];
}

void Arena::display() const
{
    snake_->print();
    //Use library daddy told me to use ! 
}
