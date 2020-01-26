#include "Interactuable.h"

namespace ui {

	Interactuable::Interactuable()
	{
	}

	void Interactuable::BlockEvent(bool block)
	{
		m_blockEvent = block;
	}

	Interactuable::~Interactuable()
	{
	}

}
