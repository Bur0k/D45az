#include "IngameLogic.h"

IngameLogic::IngameLogic()
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);
}

IngameLogic::~IngameLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}