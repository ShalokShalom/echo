#pragma once

#include "RenderState.h"
#include "ShaderProgram.h"
#include "RenderInput.h"
#include "Renderable.h"
#include <utility>

namespace rapidxml { template<class Ch> class xml_node; }

namespace Echo
{
	/**
	 * 材质
	 */
	class Renderer;
	class Material : public PtrMonitor<Material>
	{
		typedef map<String, const SamplerState*>::type SamplerStateMap;
		typedef vector<std::pair<String, String> >::type SeparatedSamplerArray;
		typedef vector<String>::type TextureSamplerStateArray;
	public:
		Material();
		~Material();

		// 获取名称
		const String& getName() { return m_name; }

		// 释放所有状态
		void free();

		// load and parse by file
		bool loadFromFile(const String& filename, const String& macros);
		bool loadShaderFrom(void* pNode);
		bool loadBlendState(void* pNode);
		bool loadMacro(void * pNode);
		bool loadRasterizerState(void* pNode);
		bool loadDepthStencilState(void* pNode);
		
		//bool loadSamplerState(void* pNode, int stage);
		bool loadSamplerState_Ext( void* pNode );
		bool loadTexture_Ext( void* pNode );

		// create manual
		void createBlendState(BlendState::BlendDesc& desc);
		void createDepthState(DepthStencilState::DepthStencilDesc& desc);
		void createRasterizerState(RasterizerState::RasterizerDesc& desc);
		//void createSamplerState(int stage, SamplerState::SamplerDesc& desc);

		// 创建着色器
		void createShaderProgram( const String& vsFileName, const String& psFileName);

		// 获取混合状态
		BlendState* getBlendState() const { return m_pBlendState; }

		// 获取深度模板状态
		DepthStencilState* getDepthState() const { return m_pDepthState; }

		// 获取光栅化状态
		RasterizerState* getRasterizerState() const { return m_pRasterizerState; }

		// 获取采样状态
		const SamplerState* getSamplerState(int stage) const;

		// 获取着色器
		ShaderProgram* getShaderProgram() const { return m_pShaderProgram; }

		// 获取顶点步幅
		size_t getVertexStrite() const { return m_VertexStrite; }

		// 绑定shader
		void activeShader();
		
		// 激活纹理(指定纹理要使用的采样状态)
		//void activeTexture(int stage, Texture* tex);

		// 设置队列
		void setQueue(RenderQueue* queue) { m_queue = queue; }

		bool			hasMacro		(const char* const macro) const;

//#ifdef ECHO_EDITOR_MODE
		// 获取材质可选宏定义列表
		static StringArray getEnabledMacros(const String& matFileName, bool withEnabled = false);


		struct DefaultUniform
		{
			i32 count;
			ShaderParamType type;
			ui32 sizeInByte;
			void* value;

			~DefaultUniform();
		};
		bool					loadDefaultUniform(void* pNode);
		const DefaultUniform*	getDefaultUniformValue(const String& name);
		void*					createDefaultUniformValue(const String& strType, const i32 count, const String& strValue, ui32& outSize, ShaderParamType& outType);
//#endif

	private:
		// 获取采样状态
		const SamplerState* getSamplerStateByTexStage(int stage);

		bool _loadColorFilter( rapidxml::xml_node<char>* pNode );

	private:
		String				m_name;
		Shader::ShaderDesc	m_shaderDesc;							// 材质使用的宏定义
		RenderQueue*		m_queue;								// 当前材质所处的渲染队列
		BlendState*			m_pBlendState;
		DepthStencilState*	m_pDepthState;
		RasterizerState*	m_pRasterizerState;
		const SamplerState*	m_pSamplerState[MAX_TEXTURE_SAMPLER];
		SamplerStateMap		m_mapSamplerState;
		TextureSamplerStateArray	m_arrTexSamplerState;
		ShaderProgram*		m_pShaderProgram;
		size_t				m_VertexStrite;
//#ifdef ECHO_EDITOR_MODE
		typedef map<String, DefaultUniform*>::type MapDefaultUniforms;
		MapDefaultUniforms	m_defaultUniforms;
//#endif // ECHO_EDITOR_MODE

	};
}
