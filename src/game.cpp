/*
 * game.cpp
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

const int NCOLORS = 7;
const int AUTOMOVE_ACTIVATION_TIME = 200; // 200
const int AUTOMOVE_INTERVAL = 40; // 40

const int block_table[448] =
{

    /* *** */
    /* *   */
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    /* *** */
    /*   * */
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,

    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    /* *** */
    /*  *  */
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    /*  ** */
    /* **  */

    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,

    /* **  */
    /*  ** */

    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,

    /* **** */
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,

    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,

    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,

    /* ** */
    /* ** */
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,

    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};


Block Block::copy()
{
	b =  Block();
	b.x = x;
	b.y = u;
	return b;
}

Shape Shape::copy()
{
	s = Shape();
	s.x = x;
	s.y = y;
	s.rotation = rotation;
	s.types = types;
	
	for(auto b : blocks)
		s.blocks.append(b.copy());
	return s;
}


#include "game.hpp"


Game::Game(int lines = 20, int columns = 10, int starting_level = 1, int filled_lines = 0, int fill_prob = 5, bool pick_difficult_blocks = false) : starting_level(starting_level), pick_difficult_blocks(pick_difficult_blocks)
{
	blocks.resize(columns, std::vector<Block*>(lines, nullptr));
	
	/* Start with some shape_landed-filled spaces */
	for (int y = 0; y < get_heigth; y++)
	{
		/* Pick at least one column to be empty */
            int blank = Random.int_range (0, get_width);

            for (int x = 0; x < width; x++)
            {
                if (y >= (get_height - filled_lines) && x != blank && Random.int_range (0, 10) < fill_prob)
                {
                    blocks[x, y] = new Block ();
                    blocks[x, y].x = x;
                    blocks[x, y].y = y;
                    blocks[x, y].color = Random.int_range (0, NCOLORS);
                }
                else
                    blocks[x, y] = null;
            }
                      
	}
	if (!pick_difficult_blocks)
		next_shape = pick_random_shape (); 
}



Game::~Game()
{
	delete b;
	delete s;
}

int Game::get_width()
{
	return blocks.length[0];
}

int Game::get_heigth()
{
	return blocks.length[1];
}

bool Game::get_paused()
{
	return m_paused;
}

bool Game::set_paused()
{
	_paused = value;
	if (has_started && !game_over)
		setup_drop_timer();
	pause_change();
}

int Game::get_shadow_y()
{
	if(shape == null)
		return 0;
		
		int d = 0;
		Game g = copy();
		while(g.move_shape(0, 1, 0))
			d++;
			
		return shape.y + d;
}


Game Game::copy()
{
	auto g = new Game();
	if(shape != nullptr)
		g.shape = shape.copy();
		
	if(next_shape != nullptr)
		g.next_shape = next_shape.copy();
		
		for (int x = 0; x < get.width; x++)
        {
            for (int y = 0; y < get.height; y++)
            {
                if (blocks[x, y] != null)
                    g.blocks[x, y] = blocks[x, y].copy ();
            }
        }
        g.n_lines_destroyed = n_lines_destroyed;
        g.score = score;
        g.starting_level = m_starting_level;
        g.pick_difficult_blocks = m_pick_difficult_blocks;
        g.fast_move_direction = m_fast_move_direction;
        g.fast_forward = m_fast_forward;
        g.has_started = m_has_started;
        g._paused = m_paused;
        g.game_over = game_over;

        return g;
		
}


void Game::start ()
{
        m_has_started = true;
        make_next_shape();
        add_shape();
        setup_drop_timer();
        started();
        pause_changed();
}


bool Game::move_left ()
{
	return move_direction (-1);
}

bool Game::move_right ()
{
	return move_direction (1);
}

bool Game::stop_moving ()
{
	if (game_over)
		return false;

	if (fast_move_timeout != 0)
		Source.remove (fast_move_timeout);
		
	fast_move_timeout = 0;
	fast_move_direction = 0;

   return true;
}

bool Game::rotate_left ()
{
	return try_rotate(1);
}

bool Game::rotate_right ()
{
	return try_rotate(-1);
}

//will rotate the tetromino and if it doesn't fit, will try to move it a little horizontaly so the rotation has the most chances of succeeding.
//Example use case: The tetromino is on the left of right side of the grid, because it will probably not fit after rotation, we move it a little so it still gets rotated if there is enough space around the tetromino.
bool Game::try_rotate (int r_step)
{
	std::list<int> listHMoves;
   listHMoves.append(0);
   listHMoves.append(1);
   listHMoves.append(-1);
   listHMoves.append(2);
   listHMoves.append(-2);

        bool result = false;

        for (int hmove : listHMoves)
        {
            //tries to move the shape
            result = move_shape(hmove, 0, r_step);
            //if rotation succeeded, we stop
            if (result) {
                break;
            }
        }

        //we return if any of our tries succeeded
        return result;
    }

void Game::set_fast_forward(bool enable)
{
	//gamestate check
	if (fast_forward == enable || game_over)
		return;

	//we move the shape down a little, according to parameters
	if (enable)
		if (!move_shape (0, 1, 0))
			return;

	fast_forward = enable;
	setup_drop_timer ();
}


void Game::drop()
{
	if (shape == null)
		return;

	while (move_shape (0, 1, 0));
		fall_timeout_cb ();
}

void Game::stop ()
{
	if (drop_timeout != 0)
		Source.remove (drop_timeout);
}

bool Game::move_direction (int direction)
{
	if (game_over)
		return false;
	if (fast_move_direction == direction)
		return true;

	if (fast_move_timeout != 0)
		Source.remove (fast_move_timeout);

	fast_move_timeout = 0;
	fast_move_direction = direction;
	
	if (!move ())
		return false;

	fast_move_timeout = Timeout.add (AUTOMOVE_ACTIVATION_TIME, setup_fast_move_cb);

	return true;
}


// Following are the two callbacks who manages the auto moving of tetrominos. setup_fast_move_cb() and move().
// Why two? As explained in a more detailled manner above the declaration of the constants AUTOMOVE_INTERVAL and AUTOMOVE_ACTIVATION_TIME,
// the logic of auto moving is kinda separated in 2 phases : the "activating" and the "activated" phase, both of which have different delays.

bool Game::setup_fast_move_cb ()
{
	if (!move ())
	{
		//it should not stop trying to move the block until the player releases the left or right key. it could happens that on the edge of the screen
      //we rotate the block then it can move a little bit more.
      //return false;
	}
	fast_move_timeout = Timeout.add (AUTOMOVE_INTERVAL, move);

	return false;
}

bool Game::move ()
{
	if (!move_shape (fast_move_direction, 0, 0))
	{
		//it should not stop trying to move the block until the player releases the left or right key. it could happens that on the edge of the screen
      //we rotate the block then it can move a little bit more.

      //fast_move_timeout = 0;
      //fast_move_direction = 0;
      //return false;
	}

   return true;
}


void Game::setup_drop_timer ()
{
	var timestep = (int) Math.round (80 + 800.0 * Math.pow (0.75, level - 1));
	timestep = int.max (10, timestep);

	/* In fast forward mode drop at the fastest rate */
	if (fast_forward)
		timestep = 80;

	if (drop_timeout != 0)
		Source.remove (drop_timeout);
	drop_timeout = 0;
	if (!paused)
		drop_timeout = Timeout.add (timestep, fall_timeout_cb);
}


bool Game::fall_timeout_cb ()
{
	/* Drop the shape down, and create a new one when it can't move */
	if (!move_shape (0, 1, 0))
	{
		/* Destroy any lines created */
      land_shape ();

      /* Add a new shape */
      add_shape ();
	}

   return true;
}


void Game::make_next_shape ()
{
	if (pick_difficult_blocks)
   {
		next_shape = pick_difficult_shapes ();
   }
   else
   {
		next_shape = pick_random_shape ();
   }
}

void Game::add_shape ()
{
	shape = (owned) next_shape;
	make_next_shape();

	for (Shape b : shape.blocks)
   {
		int x = shape.x + b.x;
      int y = shape.y + b.y;

      /* Abort if can't place there */
      if (y >= 0 && blocks[x, y] != null)
      {
      // FIXME: Place it where it can fit

         if (drop_timeout != 0)
            Source.remove (drop_timeout);
      drop_timeout = 0;
      shape = null;
      game_over = true;
      complete ();
			return;
      }
	}

	shape_added ();
}


//array to keep track of the amount of each shape we have created. it's used for a better random shape distribution algorithm
int[] distshapecount = { 0, 0, 0, 0, 0, 0, 0 }; //there are 7 different shapes


Shape Game::pick_random_shape ()
{

	int shapecount = 7; //number of existing shapes, at least in distshapecount

	//find the smallest number in distshapecount
	int lowerbound = distshapecount[0]; //pick the first. maybe it already the smallest, but we will look for smaller ones
	
	for (int i = 0; i < shapecount; i++)
	{
		if (distshapecount[i] < lowerbound) {
		lowerbound = distshapecount[i];
		}
	}

	double sum = 0d;
	//we compute the sum of the weigh of each shape. the less the shape has been given to the player, the bigger the weigh
	for (int i = 0; i < shapecount; i++)
	{
		int rel = distshapecount[i] - lowerbound;
		//we have to make sure it's not 0
		if (rel < 1) { rel = 1; }

		double weigh = 1d / (double)(rel * rel);

		sum += weigh;
	}

	//we pick the random shape
	double rndshape = sum * Random.next_double ();

	//we figure out in which area the random number landed	
	double currentpos = 0d; //our current position
	int newshape = 0; //increases by one every loop, until we find the area
	
	for (int i = 0; i < shapecount; i++)
	{
		int rel = distshapecount[i] - lowerbound;
	//we have to make sure it's not 0
		if (rel < 1) { rel = 1; }

		double weigh = 1d / (double)(rel * rel);

		currentpos += weigh;

		//if it's inside we break
		if (rndshape < currentpos) {
		break;
		}

	newshape++;
	}

	distshapecount[newshape]++;
	return make_shape (newshape, 0);
}

Shape Game::pick_difficult_shapes ()
{
	/* The algorithm comes from Federico Poloni's "bastet" game */
	var metrics = new int[NCOLORS];
	for (var type = 0; type < NCOLORS; type++)
	{
		metrics[type] = -32000;
		for (var rotation = 0; rotation < 4; rotation++)
		{
			for (var pos = 0; pos < width; pos++)
			{
				/* Copy the current game and create a block of the given type */
				var g = copy ();
				g.pick_difficult_blocks = false;
				g.shape = make_shape (type, rotation);

				/* Move tile to position from the left */
				var valid_position = true;
				while (g.move_shape (-1, 0, 0));
				
				for (var x = 0; x < pos; x++)
				{
					if (!g.move_shape (1, 0, 0))
					{
						valid_position = false;
						break;
					}
				}

				if (!valid_position)
					break;

				/* Drop the tile here and check the metric */
				var orig_lines = g.n_lines_destroyed;
				g.drop ();

				/* High metric for each line destroyed */
				var metric = (g.n_lines_destroyed - orig_lines) * 5000;

				/* Low metric for large columns */
				for (var x = 0; x < width; x++)
				{
					int y;
					for (y = 0; y < height; y++)
					{
						if (g.blocks[x, y] != null)
							break;
					}

					metric -= 5 * (height - y);
				}

				if (metric > metrics[type])
				metrics[type] = metric;

				/* Destroy this copy */
				g.stop ();
			}
		}
	}

	/* Perturb score (-2 to +2), to avoid stupid tie handling */
	for (var i = 0; i < NCOLORS; i++)
		metrics[i] += Random.int_range (-2, 2);

		/* Sorts possible_types by priorities, worst (interesting to us) first */
		var possible_types = new int[NCOLORS];
		for (var i = 0; i < NCOLORS; i++)
			possible_types[i] = i;
		
		for (var i = 0; i < NCOLORS; i++)
		{
			for (var j = 0; j < NCOLORS - 1; j++)
			{
				if (metrics[possible_types[j]] > metrics[possible_types[j + 1]])
				{
					int t = possible_types[j];
					possible_types[j] = possible_types[j + 1];
					possible_types[j + 1] = t;
				}
			}
		}

		Shape new_shape = new Shape();
		/* Actually choose a piece */
		var rnd = Random.int_range (0, 99);
		if (rnd < 75)
			new_shape = make_shape (possible_types[0], Random.int_range (0, 4));
		else if (rnd < 92)
			new_shape = make_shape (possible_types[1], Random.int_range (0, 4));
		else if (rnd < 98)
			new_shape = make_shape (possible_types[2], Random.int_range (0, 4));
		else
			new_shape = make_shape (possible_types[3], Random.int_range (0, 4));

		/* Look, this one is a great fit. It would be a shame if it wouldn't be given next */
		//next_shape = make_shape (possible_types[NCOLORS - 1], Random.int_range (0, 4));

		return new_shape;
}

Shape Game::make_shape (int type, int rotation)
{
	var shape = new Shape ();
	shape.type = type;
	shape.rotation = rotation;

	/* Place this block at top of the field */
	var offset = shape.type * 64 + shape.rotation * 16;
	var min_width = 4, max_width = 0, min_height = 4, max_height = 0;
	for (var x = 0; x < 4; x++)
	{
		for (var y = 0; y < 4; y++)
		{
			if (block_table[offset + y * 4 + x] == 0)
				continue;

		min_width = int.min (x, min_width);
		max_width = int.max (x + 1, max_width);
		min_height = int.min (y, min_height);
		max_height = int.max (y + 1, max_height);

		var b = new Block ();
		b.color = shape.type;
		b.x = x;
		b.y = y;
		shape.blocks.append (b);
		}
	}
	var block_width = max_width - min_width;
	shape.x = (width - block_width) / 2 - min_width;
	shape.y = -min_height;

	return shape;
}

void Game::land_shape ()
{
	/* Leave these blocks here */
	foreach (var b in shape.blocks)
	{
		b.x += shape.x;
		b.y += shape.y;
		blocks[b.x, b.y] = b;
	}

	var fall_distance = 0;
	var lines = new int[4];
	var n_lines = 0;
	var base_line_destroyed = false;
	for (var y = height - 1; y >= 0; y--)
	{
		var explode = true;
		for (var x = 0; x < width; x++)
		{
			if (blocks[x, y] == null)
			{
				explode = false;
				break;
			}
		}

		if (explode)
		{
			if (y == height - 1)
				base_line_destroyed = true;
			lines[n_lines] = y;
			n_lines++;
		}
	}

	lines.resize (n_lines);

	List<Block> line_blocks = null;
	for (var y = height - 1; y >= 0; y--)
	{
		var explode = true;
		for (var x = 0; x < width; x++)
		{
			if (blocks[x, y] == null)
			{
				explode = false;
				break;
			}
		}

		if (explode)
		{
			for (var x = 0; x < width; x++)
			{
				line_blocks.append (blocks[x, y]);
				blocks[x, y] = null;
			}
			fall_distance++;
		}
		else if (fall_distance > 0)
		{
			for (var x = 0; x < width; x++)
			{
				var b = blocks[x, y];
				if (b != null)
				{
					b.y += fall_distance;
					blocks[b.x, b.y] = b;
					blocks[x, y] = null;
				}
			}
		}
	}

	var old_level = level;

	/* Score points */
	n_lines_destroyed += n_lines;
	switch (n_lines)
	{
		case 0:
			break;
		case 1:
			score += 40 * level;
			break;
		case 2:
			score += 100 * level;
			break;
		case 3:
			score += 300 * level;
			break;
		case 4:
			score += 1200 * level;
			break;
	}
	
	/* You get a bonus for getting back to the base */
	if (base_line_destroyed)
		score += 10000 * level;

	/* Increase speed if level has changed */
	if (level != old_level)
		setup_drop_timer ();

	shape_landed (lines, line_blocks);
	shape = null;
}

bool Game::move_shape (int x_step, int y_step, int r_step)
{
	if (shape == null)
	return false;

	/* Check it can fit into the new location */
	rotate_shape (r_step);
	var can_move = true;
	for (var b : shape.blocks)
	{
		var x = shape.x + x_step + b.x;
		var y = shape.y + y_step + b.y;
		if (x < 0 || x >= width || y >= height || (y >= 0 && blocks[x, y] != null))
		{
			can_move = false;
			break;
		}
	}

	/* Place in the new location or put it back where it was */
	if (can_move)
	{
		shape.x += x_step;
		shape.y += y_step;

		//Raises the appropriate signals. It is possible for multiple moves to be made at once, hence the reason why they are all separated. I have experienced refresh problems when not all concerned signals are called.
		if (x_step != 0)
		{
			shape_moved ();
		}
		if (y_step != 0)
		{
			shape_dropped ();
		}
		if (r_step != 0)
		{
			shape_rotated ();
		}
	}
	else
		rotate_shape (-r_step);

	return can_move;
}

void Game::rotate_shape (int r_step)
{
	var r = shape.rotation + r_step;
	if (r < 0)
		r += 4;
	if (r >= 4)
		r -= 4;

	if (r == shape.rotation)
		return;
	shape.rotation = r;

	/* Rearrange current blocks */
	unowned List<Block> b = shape.blocks;
	var offset = shape.type * 64 + r * 16;
	for (var x = 0; x < 4; x++)
	{
		for (var y = 0; y < 4; y++)
		{
			if (block_table[offset + y * 4 + x] != 0)
			{
				b.data.x = x;
				b.data.y = y;
				b = b.next;
			}
		}
	}
}









