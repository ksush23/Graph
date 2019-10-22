#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>

void operator >> (istream& f, GraphMatrix& obj);
void operator << (ostream& f, GraphMatrix& obj);
void operator >> (istream&f, GraphStruct& obj);
void operator << (ostream& f, GraphStruct& obj);