#include "engine/core/log/Log.h"
#include "model_module.h"
#include "mesh_res.h"
#include "importer/gltf/gltf_importer.h"

namespace Echo
{
	DECLARE_MODULE(ModelModule)

	ModelModule::ModelModule()
	{
	}

	ModelModule* ModelModule::instance()
	{
		static ModelModule* inst = EchoNew(ModelModule);
		return inst;
	}

	void ModelModule::bindMethods()
	{

	}

	void ModelModule::registerTypes()
	{
		Class::registerType<MeshRes>();

	#ifdef ECHO_EDITOR_MODE
		Class::registerType<GltfImporter>();
	#endif
	}
}