//
//  explosion.h
//  Lab07
//
//  Created by Emilio on 6/17/22.
//

#pragma once

class Explosion
{
public:
   Explosion() : fragments(0.0), parts(0) {};

   float getFragments() const { return fragments; };
   float getParts() const { return parts; };

   void setFragments(float fragments) { this->fragments = fragments; };
   void setParts(float parts) { this->parts = parts; };

private:
   float fragments;
   float parts;
};
