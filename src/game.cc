/*
 * =====================================================================================
 *
 *       Filename:  game.cc
 *
 *    Description:  The actual game and functions that go with it
 *
 *        Version:  1.0
 *        Created:  14/02/2019 14:58:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Sands (js), jonathan.sands@epita.fr
 *        Company:  none
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include	<ctype.h>
#include	<iostream>
#include	<string>
#include	<stdexcept>
#include	<ncurses.h>
#include	<assert.h>
#include	<unistd.h>
#include	"include/snake.hh"


void uppercase(std::string& str)
{
    for (auto& c : str)
    {
        c = std::toupper(c);
    }
}

bool yes_no(void)
{
    std::string token;
    do
    {
        std::cout << "\nYes or No? ";
        std::getline(std::cin, token);
        uppercase(token);
    } while (token.compare("Y") && token.compare("YES") && token.compare("N") && token.compare("NO"));
    return (token[0] == 'Y');
}

void select_difficulty(ArenaBuilder& builder)
{
    std::string input;
    int res = -1;
    do
    {
        std::cout << "\nChoose a difficulty level: High (h), Medium (m), Low (l) : ";
        std::getline(std::cin, input);
        uppercase(input);
    }while (input.compare("H") && input.compare("M") && input.compare("L"));
    if (!input.compare("H"))
        res = 2;
    else if (!input.compare("M"))
        res = 1;
    else
        res = 0;
    builder.set_difficulty(res);
}

bool is_number(std::string str)
{
    for (auto c : str)
    {
        if(!isdigit(c))
            return false;
    }
    return true;

}

void select_size(ArenaBuilder& builder)
{
    unsigned max_height = 0;
    unsigned max_width = 0;
    bool choose;
    std::cout << "\nWant to choose arena_size ?";
    choose = yes_no();
    if (choose)
    {
        int height, width;
        std::string token;
        do
        {
            std::cout << "\nEnter a positive number for the height : ";
            getline(std::cin, token);
        } while(!is_number(token) || (height = std::stoi(token)) <= 0);
        do
        {
            std::cout << "\nEnter a positive number for the width : ";
            getline(std::cin, token);
        } while(!is_number(token) || (width = std::stoi(token)) <= 0);
        if(height <= 0 || width <= 0)
        {
            throw std::logic_error("Can't have negative or size in arena");
        }
        max_height = (unsigned)height;
        max_width = (unsigned)width;
    }
    builder.set_size(max_height, max_width);
}

void select_name(ArenaBuilder& builder)
{
    std::string token;
    do
    {
        std::cout << "\nWhat is your name? ";
        std::getline(std::cin, token);
    } while(token.empty());
    builder.set_player(token);
}

Arena make_arena()
{
    ArenaBuilder builder{};
    select_difficulty(builder);
    select_name(builder);
    select_size(builder);
    return builder.build();
}

void curses_routine(void)
{
    initscr();
    noecho();
    cbreak();
}

void check_size(Arena& arena)
{
    int h, w;
    getmaxyx(stdscr, h, w);
    assert(h > 0 && w > 0);
    unsigned& cur_h = arena.height();
    unsigned& cur_w = arena.width();
    cur_h = (cur_h > (unsigned)h || !cur_h) ? h : cur_h;
    cur_w = (cur_w > (unsigned)w || !cur_w) ? w : cur_w;
}

void arena_checks(Arena& arena)
{
    check_size(arena);
    assert(arena.width() > 1 && arena.height() > 1);
    arena.init();
    assert(arena.lives() > 0);
}

void start_game(Arena& arena)
{
    curses_routine();
    arena_checks(arena);
    WINDOW*& window = arena.window(); 
    keypad(window, TRUE);
    nodelay(window, TRUE);
    wattron(window, A_BOLD);
    wmove(window, 0, 0);
    int key = 0;
    int next_key;
    while (arena.lives())
    {
        next_key = wgetch(window);
        key = (next_key != ERR) ? next_key : key;
        arena.new_direction(key);
        arena.update();
        wrefresh(window);
        usleep(100000);
    }
    wattroff(window, A_BOLD);
}

int main (void)
{
    Arena arena = make_arena();
    start_game(arena);
    endwin();
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
