/*
 * shape.hpp
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


#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Block"

class Shape
{
	public:
		Shape();
		virtual ~Shape();
	
	/* Location of shape */
	int x, y;
	
	/* Rotation angle and Piece type */
	int rotation, types;
	
	/* Blocks that make up this shape */
	std::list<Block> blocks = null;
	
	 Shape copy():
	
	private:
		/* add your private declarations */
};

#endif /* SHAPE_HPP */ 