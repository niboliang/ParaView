vtk_module(vtkIOXML
  GROUPS
    StandAlone
  DEPENDS
    vtkIOXMLParser
  TEST_DEPENDS
    vtkFiltersAMR
    vtkFiltersCore
    vtkFiltersSources
    vtkImagingSources
    vtkInfovisCore
    vtkIOLegacy
    vtkTestingCore
  )