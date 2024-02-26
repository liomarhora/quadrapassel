/*
 * game.hpp
 * 
 * Copyright 2024 Suporte_BR <suporte@Workspace>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <list>
#include <sigc++/sigc++.h>


struct Block
{
		/* Location of block*/
		int x, y;
		
		/*Color of block*/
		int color;
	
		Block copy();
		Block *block;
};


struct Shape
{
	/* Location of shape */
	int x, y;
	
	/* Rotation angle and Piece type */
	int rotation, types;
	
	/* Blocks that make up this shape */
	std::list<Block> blocks = null;
	
	Shape copy():
	Shape *s;
};

class Game
{
	public:
		Game(int lines = 20, int columns = 10, starting_level = 1, int filled_lines = 0, int fill_prob = 5, bool pick_difficult_blocks = false);
		virtual ~game();
		
		 /* Falling shape */
		Shape shape = nullptr;
		
		 /* Falling shape */
		Shape next_shape = nullptr;
		
		 /* Falling shape */
		std:vector<Block> vec_blocks;
		
		
		
		/* Number of lines that have been destroyed */
		int n_lines_destroyed = 0;

		/* Game score */
		int score = 0;

		/* Level play started on */
		int starting_level = 1;

		/* The current level */
		int level { get { return starting_level + n_lines_destroyed / 10; } }
		
		Game copy();
		void start();
		void set_fast_forward(bool enable);
		void drop();
		void stop();
		bool move_left();
		bool move_right();
		bool stop_moving();
		bool rotate_left();
		bool rotate_right();
		int  get_width();
		int  get_heigth();
		
    	bool get_paused();
		bool set_paused();
		int  get_shadow_y();
		bool game_over = false;
		
		
		/*signals */
		sicg::signal<void(std::string)> started();
		sicg::signal<void(std::string)> shape_added();
		sicg::signal<void(std::string)> shape_moved();
		sicg::signal<void(std::string)> shape_dropped();
		sicg::signal<void(std::string)> shape_rotated();
		sicg::signal<void(std::string)> shape_landed(int[] lines, std::list<Blocks> line_blocks);
		sicg::signal<void(std::string)> pause_change();
		sicg::signal<void(std::string)> complete();
	
	/* add your private declarations */
	private:
		
		/* true if should pick difficult blocks to place */
		bool pick_difficult_blocks = false;
    
		/* The direction we are moving */
		int fast_move_direction = 0;

		/* Timer to animate moving fast */
		unsigned int fast_move_timeout = 0;

		/* true if we are in fast forward mode */
		bool fast_forward = false;

		/* Timer to animate block drops */
		unsigned drop_timeout = 0;

		/* true if the game has started */
		bool has_started = false;

		/* true if games is paused */
		bool _paused = false;
	
		int[] distshapecount = { 0, 0, 0, 0, 0, 0, 0 }; //there are 7 different shapes
		
		bool try_rotate(int r_step);
		bool move_direction(int direction);
		bool setup_fast_move_cb();
		bool move();
		bool fall_timeout_cb();
		void setup_drop_timer();
		void make_next_shape();
		void add_shape();
		Shape pick_random_shape();
		Shape pick_difficult_shapes();
		Shape make_shape(int type, int rotation);
		void land_shape();
		bool move_shape(int x_step, int y_step, int r_step);
		bool rotate_shape(int r_step);
		
		
		
};

#endif /* GAME_HPP */ 
