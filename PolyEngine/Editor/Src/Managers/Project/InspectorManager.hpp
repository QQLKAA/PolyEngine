#pragma once

#include <qobject.h>

#include <ECS/Scene.hpp>

#include "Configs/ProjectConfig.hpp"
#include "Widgets/Inspectors/ViewportInspectorWidget.hpp"

using namespace Poly;

class EditorApp;
class WorldInspectorWidget;
class ResourceInspectorWidget;
class EntityInspectorWidget;
class ViewportInspectorWidget;
class Command;

class InspectorManager : public QObject
{
	Q_OBJECT

	friend class InspectorWidgetBase;
	friend class EntitiesSelectionChangedCommand;

public:
	InspectorManager(EditorApp* app);

	void InitUi();

	std::unique_ptr<IRenderingDevice> GetRenderingDevice();
	PolyEditor::IEditor* GetEditor();

	Engine* GetEngine() { return EngineObj; }
	Scene* GetScene() { return SceneObj; }
	Dynarray<Entity*> GetSelectedEntities() { return SelectedEntities; }
	const ProjectConfig* GetConfig() { return Config; }
	PolyEditor::eEngineState GetEngineState() { return EngineState; }
	ViewportInspectorWidget* GetViewportInspector() { return ViewportInspector; }

public slots:
	void EngineInitializedSlot(Engine* engine);
	void EngineDeinitializedSlot();
	void StateChangedSlot(PolyEditor::eEngineState state);

	void SceneChangedSlot(Scene* world);

	void EntitiesSpawnedSlot();
	void EntitiesDestroyedSlot();
	void EntitiesModifiedSlot(Command* cmd);
	void EntitiesReparentedSlot();
	void EntitiesSelectionChangedSlot(Dynarray<Entity*> entities);

	void ComponentsAddedSlot(Dynarray<ComponentBase*> components);
	void ComponentsRemovedSlot(Dynarray<ComponentBase*> components);

signals:
	//		project signals
	void ProjectOpened();
	void ProjectClosed();

	//		engine signals
	void EngineCreated();
	void EngineInitialized();
	void EngineDeinitialized();
	void StateChanged();

	//		world signals
	void WorldChanged();

	//		entity signals
	// Entities passed as arg are the new entities, selected entities list is set to new entities.
	void EntitiesSpawned();
	// Currently selected entities are destroyed, selected entities list is cleared.
	void EntitiesDestroyed();
	// Currently selected entities were modified; any field within entity/component changed. 
	void EntitiesModified();
	// Currently selected entities are re parented to entity passed as arg.
	void EntitiesReparented();
	// Selected entities list is changed.
	void EntitiesSelectionChanged();
	
	//		component signals
	void ComponentsAdded();
	void ComponentsRemoved();

	//		other
	void Update();
	void Reload();

private:
	Engine* EngineObj = nullptr;
	Scene* SceneObj = nullptr;
	Dynarray<Entity*> SelectedEntities;
	const ProjectConfig* Config = nullptr;
	PolyEditor::eEngineState EngineState = PolyEditor::eEngineState::NONE;

	const ProjectConfig*& ConfigRef;

	WorldInspectorWidget* WorldInspector;
	ResourceInspectorWidget* ResourceInspector;
	ViewportInspectorWidget* ViewportInspector;
	EntityInspectorWidget* EntityInspector;
};