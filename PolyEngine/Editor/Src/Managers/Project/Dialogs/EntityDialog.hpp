#pragma once

#include <QtWidgets/qdialog.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtCore/qstring.h>

#include <ECS/Scene.hpp>
#include <ECS/Entity.hpp>

using namespace Poly;

class EntityDialog : public QDialog
{
public:
	EntityDialog() {}

	Dynarray<Entity*> SpawnEntities(Scene* scene, Dynarray<Entity*> parents);
	Dynarray<Entity*> GetEntitiesToDestroy(Scene* scene, Dynarray<Entity*> entities);
	Dynarray<Entity*> ReparentEntities(Scene* scene, Dynarray<Entity*> entities, Entity* parent = nullptr);

	bool OperationCanceled() { return Canceled; }

private:
	void AddEntity(Entity* entity);
	void AddPrefab(QString prefabName);

	bool Canceled = true;
	Dynarray<Entity*> PredefinedEntities;
	std::map<QTreeWidgetItem*, Entity*> ItemToEntity;

	QGridLayout* MainLayout;
	QLabel* FirstLabel;
	QTreeWidget* EntitiesTree;
	QLabel* SecondLabel;
	QTreeWidget* PrefabTree;
	QPushButton* CancelButton;		QPushButton* OkButton;

private slots:
	void Ok();
	void Cancel();
};