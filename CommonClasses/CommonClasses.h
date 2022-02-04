// MathLibrary.h - Contains declarations of math functions
#pragma once
#include <iostream>
#include "Post.h"
#include "PostPersonalProfile.h"
#include "Repost.h"
#include "CommentServer.h"

#ifdef COMMONCLASSES_EXPORTS
#define COMMONCLASSES_API __declspec(dllexport)
#else
#define COMMONCLASSES_API __declspec(dllimport)
#endif