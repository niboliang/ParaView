/*
 * Copyright 2004 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */

#include "pqTestCases.h"

#include <vtkstd/string>

#include <QAbstractButton>
#include <QAction>
#include <QObject>
#include <QWidget>
#include <QtTest>
#include <QtTest/qttest_gui.h>

namespace
{

/// Given a Qt object, lookup a child object by name, treating the name as a hierarchical "path"
template<typename T>
T* pqLookupObject(QObject& Object, const char* Name)
{
  const vtkstd::string name = Name ? Name : "";
  const vtkstd::string part = name.substr(0, name.find("/"));
  const vtkstd::string remaining = (part.size() + 1) < name.size() ? name.substr(part.size() + 1) : "";
  
  if(remaining.empty())
  {
    QList<T*> children = Object.findChildren<T*>(part.c_str());
    if(children.size() != 1)
      return 0;
      
    return children[0];
  }
  
  QList<QObject*> children = Object.findChildren<QObject*>(part.c_str());
  if(children.size() != 1)
    return 0;

  return pqLookupObject<T>(*children[0], remaining.c_str());
}

bool pqActivate(QAction* Action)
{
  if(Action)
    Action->activate(QAction::Trigger);
    
  return Action ? true : false;
}

bool pqActivate(QAbstractButton* Button)
{
  if(Button)
    Button->click();
    
  return Button ? true : false;
}

} // namespace


/////////////////////////////////////////////////////////////////////////
// pqTestTestingFramework

void pqTestTestingFramework::testSuccess()
{
  COMPARE(true, true);
}

void pqTestTestingFramework::testFailure()
{
  EXPECT_FAIL("", "Deliberate failure", Continue);
  COMPARE(true, false);
}

//////////////////////////////////////////////////////////////////////////
// pqTestFileMenu

pqTestFileMenu::pqTestFileMenu(QWidget& RootWidget) :
  rootWidget(RootWidget)
{
}

void pqTestFileMenu::testFileMenu()
{
  VERIFY(pqLookupObject<QWidget>(rootWidget, "menuBar/fileMenu"));
}

void pqTestFileMenu::testFileOpen()
{
  VERIFY(pqActivate(pqLookupObject<QAction>(rootWidget, "debugOpenLocalFilesAction")));
  VERIFY(pqLookupObject<QWidget>(rootWidget, "fileOpenDialog"));
  VERIFY(pqActivate(pqLookupObject<QAbstractButton>(rootWidget, "fileOpenDialog/buttonCancel")));
}

