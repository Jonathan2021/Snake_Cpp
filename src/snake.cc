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
#include	"include/snake.hh"



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

std::shared_ptr<Something> Snake::clone(void)
{
    return std::make_shared<Snake>(coords());
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

std::shared_ptr<Something> Food::clone(void)
{
    return std::make_shared<Food>(increase_,color(), deadly(), coords());
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
    banana_count++;
}  /* -----  end of method Banana::Banana  (constructor)  ----- */

Banana::Banana (const std::pair<unsigned, unsigned> coords)
    :Food(3, yellow, false, coords)
{
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

std::shared_ptr<Something> Banana::clone(void)
{
    return std::make_shared<Banana>(coords());
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
    mushroom_count++;
} /* -----  end of method Mushroom::Mushroom  (constructor)  ----- */

Mushroom::Mushroom (const std::pair<unsigned, unsigned> coords)
    :Food(-3, red, true, coords)
{
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

std::shared_ptr<Something> Mushroom::clone(void)
{
    return std::make_shared<Mushroom>(coords());
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

std::shared_ptr<Something> LifeUp::clone(void)
{
    return std::make_shared<LifeUp>(coords());
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

std::shared_ptr<Something>& Arena::head(void)
{
    return this->snake_.front();
}

std::shared_ptr<Something>& Arena::tail(void)
{
    return this->snake_.back();
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

bool& Arena::colored(void)
{
    return colored_;
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
    if (key == direction_ || (key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT))
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

void Arena::add_to_window(unsigned y, unsigned x, char c = ' ', Color color = no_color)
{
    if (colored_)
    {
        c = ' ';
        wattron(window_, COLOR_PAIR(color));
    }
    mvwaddch(window_, y, x, c);
    if (colored_)
        wattroff(window_, COLOR_PAIR(color));
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
    arena.add_to_window(something->coords().first, something->coords().second, something->print(), something->color());
}

void Arena::add_something(std::shared_ptr<Something> something)
{
    auto& vect = get_vect(*this, something); 
    get_pos(something->coords()) = something;
    vect.insert(vect.begin(), something);
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
                arena.add_to_window(pos.first, pos.second);
            }
            vect.erase(it, it + nb);
            break;
        }
    }
}

void Arena::remove_something(std::shared_ptr<Something> something, int nb)
{
    auto& vect = get_vect(*this, something);
    if (vect.empty())
    {
        throw std::logic_error("trying to remove something from nothing");
    }
    my_erase(vect, something, nb, *this);
}

void suround(Arena& arena)
{
    unsigned w = arena.width();
    unsigned h = arena.height();
    for(unsigned i = 0; i < w; ++i)
    {
        arena.add_something(std::make_shared<Wall>(0, i));
        arena.add_something(std::make_shared<Wall>(h - 1, i));
    }
    for (unsigned i = 0; i < h; ++i)
    {
        arena.add_something(std::make_shared<Wall>(i, 0));
        arena.add_something(std::make_shared<Wall>(i, w - 1));
    }
}

template <typename T>
bool is_uninitialized(std::weak_ptr<T> const& weak) {
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

void random_pos(Arena& arena, std::shared_ptr<Something> something)
{
    unsigned rand_y;
    unsigned rand_x;
    unsigned h = arena.height();
    unsigned w = arena.width();
    do
    {
        rand_y = rand() % h;
        rand_x = rand() % w;
    } while(!arena.get_pos(rand_y, rand_x).expired());
    something->coords() = std::make_pair(rand_y, rand_x);
}

void random_place(Arena& arena, std::shared_ptr<Something> something)
{
    random_pos(arena,something);
    arena.add_something(something);
}

void Arena::init(void)
{
    window_ = newwin(height_, width_, 0, 0);
    lives_ = 3 - difficulty_;
    map_ = new std::weak_ptr<Something>*[height_];
    for (unsigned i = 0; i < height_; ++i)
        map_[i] = new std::weak_ptr<Something>[width_]();
    suround(*this);
    if (snake_.empty())
    {
        add_something(std::make_shared<Snake>(height_ / 2 , width_ / 2));
        growth_ = 2;
    }
    unsigned y_temp;
    unsigned x_temp;
    for (auto i = 0; i < 4; ++i)
    {
        if (i < difficulty_)
            random_place(*this, std::make_shared<Mushroom>(y_temp, x_temp));
        else
            random_place(*this, std::make_shared<Banana>(y_temp, x_temp));
    }
}

std::pair<unsigned, unsigned> ahead(Arena& arena)
{
    auto cur = arena.head()->coords();
    int dir = arena.direction();
    unsigned h = arena.height();
    unsigned w = arena.width();
    if (dir == KEY_UP)
    {
        cur.first -= 1;
        if (cur.first >= h)
            cur.first = h - 1;

    }
    else if (dir == KEY_DOWN)
    {
        cur.first += 1;
        if (cur.first >= h)
            cur.first = 0;
    }
    else if (dir == KEY_LEFT)
    {
        cur.second -= 1;
        if (cur.first >= w)
            cur.first = w - 1;
    }
    else if (dir == KEY_RIGHT)
    {
        cur.second += 1;
        if (cur.first >= w)
            cur.first = 0;
    }
    assert(arena.in_bound(cur));
    return cur;
}

void remove_tail(Arena& arena)
{
    arena.remove_something(arena.tail(), 1);
}

void remove_head(Arena& arena)
{
    arena.remove_something(arena.head(), 1);
}

void Arena::update(void)
{
    if (!direction_)
        return;
    auto pos = ahead(*this);
    assert(pos != head()->coords());
    auto element = get_pos(pos);
    if (!element.expired())
    {
        element.lock()->trigger(*this);
        pos = (ahead(*this));
    }
    assert(pos != head()->coords());
    add_something(std::make_shared<Snake>(pos));
    if(growth_ > 0)
    {
        growth_--;
        return;
    }
    else if (growth_ < 0)
    {
        if (!snake_.empty())
            remove_tail(*this);
        growth_++;
    }
    remove_tail(*this);
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

std::shared_ptr<Something> Wall::clone(void)
{
    return std::make_shared<Wall>(coords());
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
    auto food = arena.food();
    for (auto it = food.begin(); it != food.end(); ++it)
    {
        if ((*it).get() == this)
        {
            arena.add_to_window((*it)->coords().first, (*it)->coords().second);
            arena.growth() += (std::dynamic_pointer_cast<Food>(*it))->increase();
            if ((*it)->deadly())
                arena.lives()--; 
            auto baby = (*it)->clone();
            random_pos(arena, baby);
            arena.remove_something(*it, 1);
            arena.add_something(baby);
            break;
        }
    }
}

void Wall::trigger(Arena& arena)
{
    remove_head(arena);
    arena.lives()--;
}

