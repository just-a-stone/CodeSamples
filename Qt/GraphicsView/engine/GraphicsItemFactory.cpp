/**
 * This work is licensed under the Creative Commons Attribution 3.0 Unported 
 * License. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by/3.0/ or send a letter to Creative 
 * Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include <QDebug>
#include <QDir>
#include <QLibrary>

#include "GraphicsSheet.h"
#include "GraphicsItemFactory.h"

typedef void (*ItemMain)(GraphicsItemFactory*);

GraphicsItemFactory::GraphicsItemFactory() {

    // search all shared libraries below the bin directory where the
    // base name ends with "items":
    QDir itemsDir("bin");
    QStringList names;
    names << "*items.dll" << "*items.so";  // TODO: better approach?
    QStringList itemLibs = itemsDir.entryList(names);
    foreach(QString libName, itemLibs) {
        QString libPath = itemsDir.path() + QDir::separator() + libName;
        qDebug() << "Loading: " << libPath;

        QLibrary itemLibrary(libPath);
        itemLibrary.load();

        ItemMain itemMain = (ItemMain) itemLibrary.resolve("ItemsMain");
        itemMain(this);
    }
}


void GraphicsItemFactory::registerItemClass(const QString& className, FACTORY_FUNCTION fac) {
    factoryFunctions.insert(className, fac);
}


QGraphicsItem* GraphicsItemFactory::createItem(const QString& className) {
    QGraphicsItem* result = 0;

    FACTORY_FUNCTION fac = factoryFunctions.value(className);
    if (fac) {
        result = fac();
    }

    return result;
}