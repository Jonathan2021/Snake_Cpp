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
#include	<ncurses.h>
#include	<string>
#include	<stdexcept>
#include	"snake.hh"


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
    }while (input.compare("h") && input.compare("m") && input.compare("l"));
    if (!input.compare("h"))
        res = 2;
    else if (!input.compare("m"))
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
    int max_height, max_width;
    bool choose;
    getmaxyx(stdscr, max_height, max_width);
    std::cout << "Want to choose arena_size ?";
    choose = yes_no();
    if (choose)
    {
        int height, width;
        std::string token;
        do
        {
            std::cout << "\nEnter a number for the height : ";
            getline(std::cin, token);
        } while(!is_number(token));
        height = std::stoi(token);
        do
        {
            std::cout << "\nEnter a number for the width : ";
            getline(std::cin, token);
        } while(!is_number(token));
        width = std::stoi(token);
        max_height = (max_height < height) ? max_height : height;
        max_width = (max_width < width) ? max_width : width;
    }
    if(max_height <= 0 || max_width <= 0)
    {
        throw std::logic_error("Can't have negative or size in arena");
    }
    builder.set_size(max_height, max_width);
}

void select_name(ArenaBuilder& builder)
{
    std::string token;
    std::cout << "What is your name? ";
    std::getline(std::cin, token);
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
    stdscr = initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void start_game(Arena& arena)
{
    curses_routine();
    WINDOW* window =  newwin(arena.height(), arena.width(), 0, 0);
    wmove(window, 0, 0);
    int key = 0;
    int next_key;
    while (arena.lives())
    {
        next_key = getch();
        key = (next_key != ERR) ? next_key : key;
        arena.new_direction(key);
        arena.update();
        wrefresh(window);
    }
    endwin();
}

int main (void)
{
    Arena arena = make_arena();
    start_game(arena);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
