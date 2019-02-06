//
//  Game.cpp
//  dirtyclient
//
//  Created by Eugene Sturm on 2/3/19.
//

#include "Game.hpp"
#include "Connection.hpp"

void Game::initialize(gfx::RenderDevice* device, gfx::Swapchain* swapchain, ConnectionPtr& connection)
{
    _device = device;
    _swapchain = swapchain;
    _connection = connection;
    
    gfx::ColorAttachmentDesc colorAttachment;
    colorAttachment.format = _swapchain->pixelFormat();
    colorAttachment.loadAction = gfx::LoadAction::Clear;
    colorAttachment.storeAction = gfx::StoreAction::DontCare;
    colorAttachment.clearColor = { 0, 1, 0, 1 };
    colorAttachment.index = 0;
    
    gfx::RenderPassInfo renderPassInfo;
    renderPassInfo.addColorAttachment(colorAttachment);
    
    _renderPassId = _device->CreateRenderPass(renderPassInfo);
}

void Game::update(const std::vector<SDL_Event>& systemEvents, const std::vector<Packet>& packets, double dt)
{
    for (const Packet& packet : packets) {
        const MessageType type = packet.read<MessageType>();
        switch (type) {
            case MessageType::LoginResponse: {
                
                break;
            }
            default: {
                std::cout << "unexpected:" << to_string(type) << std::endl;
                break;
            }
        }
    }
    
    
    
    gfx::TextureId backbuffer = _swapchain->begin();
    
    gfx::FrameBuffer frameBuffer;
    frameBuffer.setColorAttachment(backbuffer, 0);
    
    gfx::CommandBuffer* commandBuffer = _device->CreateCommandBuffer();
    gfx::RenderPassCommandBuffer* renderPassCommandBuffer = commandBuffer->beginRenderPass(_renderPassId, frameBuffer, "rawr");
    
    commandBuffer->endRenderPass(renderPassCommandBuffer);
    _device->Submit({commandBuffer});
    
    _swapchain->present(backbuffer);
    
}

void Game::shutdown()
{
    
}
