#include "TextureBindManager.h"
#include "TextureBinding.h"

using namespace Crawfis::Graphics;

bool Crawfis::Graphics::TextureBindManager::created = false;
Crawfis::Graphics::TextureBindManager* Crawfis::Graphics::TextureBindManager::instance = 0;

TextureBinding* Crawfis::Graphics::TextureBindManager::CreateNewBinding(ITextureDataObject* texture, ITextureApplicator* textureApplicator)
{
	return new TextureBinding(texture, textureApplicator);
}
bool Crawfis::Graphics::TextureBindManager::getIsBound( TextureBinding* binding)
{
	return binding->isBound;
}
void Crawfis::Graphics::TextureBindManager::setIsBound( TextureBinding* binding, bool isBound)
{
	binding->isBound = isBound;
}
int Crawfis::Graphics::TextureBindManager::getHardwareSlot( TextureBinding* binding)
{
	return binding->hardwareSlot;
}
void Crawfis::Graphics::TextureBindManager::setHardwareSlot( TextureBinding* binding, int slot)
{
	binding->hardwareSlot = slot;
}
void Crawfis::Graphics::TextureBindManager::BindInternal(TextureBinding* binding)
{
	binding->texture->Enable();
	binding->textureApplicator->Apply(binding->hardwareSlot);
}
void Crawfis::Graphics::TextureBindManager::UnbindInternal(TextureBinding* binding)
{
	binding->texture->Disable();
	binding->textureApplicator->Unapply(binding->hardwareSlot);
}
