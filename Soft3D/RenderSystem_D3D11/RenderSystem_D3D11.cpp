#include "RenderSystem_D3D11.h"

namespace Soft3D {

	Bool RenderSystemD3D11::InitalizeWindow(const RenderConfig& config) {
		return true;
	}


	void RenderSystemD3D11::DestoryWindow() {

	}

	void RenderSystemD3D11::OnChangeSize(UInt width, UInt height) {
		
	}

	void RenderSystemD3D11::SetViewport(const Viewport& viewport) {

	}

	Viewport RenderSystemD3D11::GetViewport() {
		return Viewport(0,0);
	}

	void RenderSystemD3D11::Clear(const Color& color) {

	}
	void RenderSystemD3D11::Flush() {

	}

	void RenderSystemD3D11::SwapBuffer() {

	}

	void RenderSystemD3D11::SetPointSize(Float size) {

	}

	Float RenderSystemD3D11::GetPointSize() {
		return 0;
	}

	void RenderSystemD3D11::SetLineWidth(Float width) {

	}

	Float RenderSystemD3D11::GetLineWidth() {
		return 0;
	}

	void RenderSystemD3D11::SetBrushColor(const Color& color) {

	}

	Color RenderSystemD3D11::GetBrushColor() {
		return Color();
	}

	void RenderSystemD3D11::SetProjectionMatrix(const Matrix4& projectionMatrix) {

	}

	Matrix4& RenderSystemD3D11::GetProjectionMatrix() {
		return Matrix4();
	}

	void RenderSystemD3D11::SetTransformMatrix(const Matrix4& transformMatrix) {

	}

	Matrix4& RenderSystemD3D11::GetTransformMatrix() {
		return Matrix4();
	}

	void RenderSystemD3D11::EnableDepthTest() {

	}

	void RenderSystemD3D11::DisableDepthTest() {

	}

	void RenderSystemD3D11::EnableStencilTest() {

	}

	void RenderSystemD3D11::DisableStencilTest() {

	}


	UInt RenderSystemD3D11::AddTexture(Texture& texture) {
		return 0;
	}

	void RenderSystemD3D11::DelTexture(UInt textureId) {

	}

	void RenderSystemD3D11::EnableTexture(UInt textureId) {

	}

	void RenderSystemD3D11::DisableTexture(UInt textureId) {

	}

	UInt RenderSystemD3D11::AddLight(Light& light) {
		return 0;
	}

	void RenderSystemD3D11::DelLight(UInt light) {

	}

	void RenderSystemD3D11::EnableLight(UInt light) {

	}

	void RenderSystemD3D11::DisableLight(UInt light) {

	}

	void RenderSystemD3D11::SetBlendMode(const BlendMode& blendMode) {

	}

	BlendMode RenderSystemD3D11::GetBlendMode() {
		return BlendMode();
	}

	void RenderSystemD3D11::CachePrimitivew(Primitivew primit) {

	}

	void RenderSystemD3D11::DrawPrimitivew(const Primitivew& primit) {

	}

	UInt RenderSystemD3D11::AddShader(Shader& shader) {
		return 0;
	}

	void RenderSystemD3D11::DelShader(UInt  shaderId) {

	}

	void RenderSystemD3D11::EnableShader(UInt shaderId) {

	}

	void RenderSystemD3D11::DisableShader(UInt shaderId) {

	}

}
