/*
 *  GNU Lesser General Public License (LGPL):
 *
 *	Copyright (C) 2016  ProgSys
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, version 3 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with this program.  If not, see http://doc.qt.io/qt-5/lgpl.html
 *	or http://www.gnu.org/licenses/
 */
#ifndef INCLUDE_PG_OPENGL_PG_TEXTURE_H_
#define INCLUDE_PG_OPENGL_PG_TEXTURE_H_

#include <openGL/PG_GLItem.h>
#include <pg/util/PG_Image.h>

namespace PG {
namespace GL {

class Texture: public GLItem {
public:
	Texture();

	void bind(const PG::UTIL::IDImage& img);
	void bind(const PG::UTIL::RGBImage& img);
	void bind(const PG::UTIL::RGBAImage& img);

	void apply() const;

	void release() const;

	virtual ~Texture();
private:
	bool create();
	bool setTexture(unsigned char* imagedata, int type, const unsigned int width, const unsigned int height, bool freedata = false, bool flipYAxis = false);
};

} /* namespace GL */
} /* namespace PG */

#endif /* INCLUDE_PG_OPENGL_PG_TEXTURE_H_ */
