# AutoCAD Plant 3D API Development Guide

This guide provides essential patterns and best practices for developing Plant 3D add-ons using the .NET API.

## Table of Contents
- [Core Concepts](#core-concepts)
- [Essential Namespaces](#essential-namespaces)
- [Method Chaining Patterns](#method-chaining-patterns)
- [Common API Workflows](#common-api-workflows)
- [Best Practices](#best-practices)

---

## Core Concepts

### 1. Manager Pattern (Singleton Access)

Plant 3D uses a manager pattern for accessing core functionality. Managers are typically accessed via static methods:

```csharp
// Project access
Project currentProject = PlantApplication.CurrentProject.ProjectParts["Piping"];
Project pnidProject = PlantApplication.CurrentProject.ProjectParts["PnId"];

// Spec manager (singleton)
SpecManager specMgr = SpecManager.GetSpecManager();

// Content manager (singleton)
ContentManager cm = ContentManager.GetContentManager();

// DataLinks manager
DataLinksManager dlm = currentProject.DataLinksManager;
DataLinksManager3d dlm3d = DataLinksManager3d.Get3dManager(dlm);
```

### 2. Transaction Pattern (ALWAYS Required)

**CRITICAL**: All database operations MUST be wrapped in transactions. The pattern is:

```csharp
Database db = AcadApp.DocumentManager.MdiActiveDocument.Database;
using (Transaction tr = db.TransactionManager.StartTransaction())
{
    // 1. Create or modify entities
    Pipe pipe = new Pipe();
    pipe.StartPoint = startPoint;
    pipe.EndPoint = endPoint;

    // 2. MUST call AddNewlyCreatedDBObject before commit
    tr.AddNewlyCreatedDBObject(pipe, true);

    // 3. Commit changes
    tr.Commit();
}
```

**Key Points**:
- Opening objects: `tr.GetObject(objectId, OpenMode.ForRead)` or `OpenMode.ForWrite`
- Always call `tr.AddNewlyCreatedDBObject(entity, true)` for NEW entities
- Call `tr.Commit()` at the end (failure to commit = no changes saved)

---

## Essential Namespaces

### AutoCAD Core
```csharp
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
```

### Plant 3D Piping
```csharp
using Autodesk.ProcessPower.PnP3dObjects;
using Autodesk.ProcessPower.AcPp3dObjectsUtils;
using Autodesk.ProcessPower.PlantInstance;
using Autodesk.ProcessPower.ProjectManager;
using Autodesk.ProcessPower.DataLinks;
using Autodesk.ProcessPower.PnP3dDataLinks;
using Autodesk.ProcessPower.P3dProjectParts;
using Autodesk.ProcessPower.PartsRepository;
using Autodesk.ProcessPower.PnP3dPipeRouting;
```

### Plant 3D PnID
```csharp
using Autodesk.ProcessPower.PnIDObjects;
```

### Useful Aliases
```csharp
using AcadApp = Autodesk.AutoCAD.ApplicationServices.Application;
using PlantApp = Autodesk.ProcessPower.PlantInstance.PlantApplication;
```

---

## Method Chaining Patterns

### Pattern 1: Part Creation Chain

The typical pattern for creating piping components:

```csharp
// 1. Fetch spec part with filters
StringCollection propertyNames = new StringCollection();
StringCollection propertyValues = new StringCollection();
propertyNames.Add("NominalDiameter");
propertyValues.Add("6");

SpecPart specPart = FetchSpecPart("Pipe", propertyNames, propertyValues);

// 2. Create entity
Pipe pipe = new Pipe();

// 3. Set properties (method chaining)
pipe.StartPoint = new Point3d(0, 0, 0);
pipe.EndPoint = new Point3d(100, 0, 0);
pipe.OuterDiameter = (double)specPart.PropValue("MatchingPipeOd");

// 4. Add to database
ObjectId pipeId = AddToDatabase(specPart, pipe, db, dlm3d);
```

### Pattern 2: Position and Orientation Chain

```csharp
// Set position
fitting.Position = new Point3d(x, y, z);

// Set orientation (X-axis direction, Z-axis direction)
fitting.SetOrientation(new Vector3d(1, 0, 0), new Vector3d(0, 0, 1));

// Alternative: Transform with matrix
Matrix3d transform = Matrix3d.Displacement(new Vector3d(10, 0, 0));
fitting.TransformBy(transform);
```

### Pattern 3: Port and Connection Chain

```csharp
// 1. Get ports from entity
PortCollection ports = part.GetPorts(PortType.Static);

// 2. Create port pairs
Pair pair1 = new Pair();
pair1.ObjectId = pipe1Id;
pair1.Port = ports["S2"];  // Port by name

Pair pair2 = new Pair();
pair2.ObjectId = connectorId;
pair2.Port = connectorPorts["S1"];

// 3. Connect using ConnectionManager
ConnectionManager cm = new ConnectionManager();
cm.Connect(pair1, pair2);
```

### Pattern 4: Connector Creation Chain

```csharp
// 1. Fetch connector spec parts
PartSizePropertiesCollection connectionPropColl =
    FetchConnectorSpecParts(propertyNames, propertyValues, "Buttweld");

// 2. Create connector
Connector connector = new Connector();
connector.SlopeTolerance = 0.1;
connector.OffsetTolerance = 0.0;

// 3. Add subparts (for composite connectors)
foreach (PartSizeProperties psp in connectionPropColl)
{
    if (psp.Type.ToLower() == "gasket")
    {
        BlockSubPart blockSubPart = new BlockSubPart();
        blockSubPart.SymbolId = cm.GetSymbol(psp, db);
        connector.AddSubPart(blockSubPart);
    }
}

// 4. Position connector
connector.Position = nextPartPos;
connector.SetOrientation(new Vector3d(1, 0, 0), new Vector3d(0, 0, 1));
```

---

## Common API Workflows

### Workflow 1: Creating a Complete Pipe Assembly

```csharp
// Initialize managers
Database db = AcadApp.DocumentManager.MdiActiveDocument.Database;
Project currentProject = PlantApp.CurrentProject.ProjectParts["Piping"];
DataLinksManager dlm = currentProject.DataLinksManager;
DataLinksManager3d dlm3d = DataLinksManager3d.Get3dManager(dlm);
PipingObjectAdder pipeObjAdder = new PipingObjectAdder(dlm3d, db);

using (Transaction tr = db.TransactionManager.StartTransaction())
{
    // 1. Create pipe
    SpecPart pipePart = FetchSpecPart("Pipe", propertyNames, propertyValues);
    Pipe pipe = new Pipe();
    pipe.StartPoint = Point3d.Origin;
    pipe.EndPoint = new Point3d(60, 0, 0);
    pipe.OuterDiameter = (double)pipePart.PropValue("MatchingPipeOd");

    pipeObjAdder.Add(pipePart, pipe);
    ObjectId pipeId = pipe.ObjectId;
    tr.AddNewlyCreatedDBObject(pipe, true);

    // 2. Get next position
    Point3d nextPos = FetchNextPartsPosition(pipeId, 1, db);

    // 3. Create connector
    PartSizePropertiesCollection connPropColl =
        FetchConnectorSpecParts(propertyNames, propertyValues, "Buttweld");
    Connector connector = CreateConnector(connPropColl, db, cm, currentProject);
    connector.Position = nextPos;
    connector.SetOrientation(new Vector3d(1, 0, 0), new Vector3d(0, 0, 1));

    pipeObjAdder.Add("Buttweld", connPropColl, connector);
    ObjectId connectorId = connector.ObjectId;
    tr.AddNewlyCreatedDBObject(connector, true);

    // 4. Connect parts
    ConnectParts(pipeId, "S2", connectorId, "S1", db, currentProject);

    tr.Commit();
}
```

### Workflow 2: Fetching Spec Parts with Filters

```csharp
public static SpecPart FetchSpecPart(
    string partType,
    StringCollection propertyNames,
    StringCollection propertyValues)
{
    SpecManager specMgr = SpecManager.GetSpecManager();
    string specName = "CS300"; // Your spec name

    if (specMgr.HasType(specName, partType))
    {
        SpecPartReader reader = specMgr.SelectParts(
            specName,
            partType,
            propertyNames,
            propertyValues);

        while (reader.Next())
        {
            SpecPart specPart = reader.Current;

            // Verify nominal diameter matches
            if (specPart.Type.Equals(partType) &&
                specPart.NominalDiameter.Value == desiredSize)
            {
                return specPart;
            }
        }
    }

    return null;
}
```

### Workflow 3: Connecting Parts

```csharp
public static void ConnectParts(
    ObjectId objectId1,
    string portName1,
    ObjectId objectId2,
    string portName2,
    Database db,
    Project currentProject)
{
    using (Transaction tr = db.TransactionManager.StartTransaction())
    {
        ConnectionManager cm = new ConnectionManager();

        // Get parts
        Part part1 = tr.GetObject(objectId1, OpenMode.ForRead) as Part;
        Part part2 = tr.GetObject(objectId2, OpenMode.ForRead) as Part;

        // Get ports
        PortCollection ports1 = part1.GetPorts(PortType.Static);
        PortCollection ports2 = part2.GetPorts(PortType.Static);

        // Create pairs
        Pair pair1 = new Pair();
        pair1.Port = ports1[portName1];
        pair1.ObjectId = objectId1;

        Pair pair2 = new Pair();
        pair2.Port = ports2[portName2];
        pair2.ObjectId = objectId2;

        // Connect
        cm.Connect(pair1, pair2);

        tr.Commit();
    }
}
```

### Workflow 4: Using PipingObjectAdder

**IMPORTANT**: PipingObjectAdder is the recommended way to add piping objects to the database.

```csharp
using (Transaction tr = db.TransactionManager.StartTransaction())
{
    using (PipingObjectAdder pipeObjAdder = new PipingObjectAdder(dlm3d, db))
    {
        // Add pipe
        if (part.GetType() == typeof(Pipe))
        {
            Pipe pipe = part as Pipe;
            pipeObjAdder.Add(specPart, pipe);
        }
        // Add inline asset (fitting, valve, etc.)
        else if (part.GetType() == typeof(PipeInlineAsset))
        {
            PipeInlineAsset asset = part as PipeInlineAsset;
            pipeObjAdder.Add(specPart, asset);
        }
        // Add connector
        else if (part.GetType() == typeof(Connector))
        {
            Connector connector = part as Connector;
            pipeObjAdder.Add(connectionName, connectionPropColl, connector);
        }

        ObjectId partId = part.ObjectId;
        tr.AddNewlyCreatedDBObject(part, true);
    }

    tr.Commit();
}
```

### Workflow 5: Getting and Setting DataLinks Properties

```csharp
// Get DataLinks manager
DataLinksManager dlm = DataLinksManager.GetManager(dlmName);

// Get all properties
List<KeyValuePair<string, string>> properties = dlm.GetAllProperties(objectId, true);

// Read specific property
foreach (var prop in properties)
{
    if (prop.Key == "PropertyName")
    {
        string value = prop.Value;
    }
}

// Set properties
StringCollection names = new StringCollection();
StringCollection values = new StringCollection();
names.Add("PropertyName");
values.Add("PropertyValue");

dlm.SetProperties(objectId, names, values);
```

### Workflow 6: Line Number and Tagging

```csharp
// Get line group ID from object
int groupId = PnP3dTagFormat.lineGroupIdFromObjId(objectId);

// Get line number from group
string lineNumber = PnP3dTagFormat.lineNumberTagFromGroup(groupId);

// Create or find line group
int newGroupId = PnP3dTagFormat.findOrCreateNewLineGroup(lineNumber);
```

---

## Best Practices

### 1. Always Use Transactions
```csharp
// WRONG - No transaction
Pipe pipe = new Pipe();
pipe.StartPoint = Point3d.Origin;

// RIGHT - With transaction
using (Transaction tr = db.TransactionManager.StartTransaction())
{
    Pipe pipe = new Pipe();
    pipe.StartPoint = Point3d.Origin;
    tr.AddNewlyCreatedDBObject(pipe, true);
    tr.Commit();
}
```

### 2. Exception Handling Pattern
```csharp
Editor ed = AcadApp.DocumentManager.MdiActiveDocument.Editor;

try
{
    using (Transaction tr = db.TransactionManager.StartTransaction())
    {
        // Your code here
        tr.Commit();
    }
}
catch (System.Exception ex)
{
    ed.WriteMessage("Error: " + ex.Message);
}
```

### 3. Use Helper Classes for Complex Operations
```csharp
// For alignment calculations
Matrix3d mat = RoutingHelper.CalculateAttachMatrix(
    port1,
    RoutingHelper.CalculateNormal(port1, null),
    port2,
    RoutingHelper.CalculateNormal(port2, null));
entity.TransformBy(mat);

// For connecting with alignment
RoutingHelper.Connect(pair1, pair2, false, false, false, groupId, null, Tolerance.Global);
```

### 4. Checking Object Types
```csharp
// Check if ObjectId is derived from a type
if (objectId.ObjectClass.IsDerivedFrom(RXObject.GetClass(typeof(Pipe))))
{
    using (Transaction tr = db.TransactionManager.StartTransaction())
    {
        Pipe pipe = tr.GetObject(objectId, OpenMode.ForRead) as Pipe;
        // Work with pipe
        tr.Commit();
    }
}
```

### 5. NominalDiameter Handling
```csharp
// Create nominal diameter
NominalDiameter nd = new NominalDiameter("in", 6.0);

// From display string
NominalDiameter nd = NominalDiameter.FromDisplayString(null, sizeString);

// Compare nominal diameters
if (nd1.Equals(nd2))
{
    // Same size
}
```

### 6. Port Access Patterns
```csharp
// Get ports by type
PortCollection staticPorts = part.GetPorts(PortType.Static);

// Access by index
Port port = staticPorts[0];

// Access by name
Port port = staticPorts["S1"];

// Check if port is connected
ConnectionManager cm = new ConnectionManager();
bool isConnected = cm.IsConnected(pair);
```

### 7. Command Registration
```csharp
// Register command with proper attributes
[CommandMethod("MyCommand")]
public static void MyCommand()
{
    // Command implementation
}

// Register assembly as extension application (if needed)
[assembly: ExtensionApplication(typeof(MyExtensionApp))]
[assembly: CommandClass(typeof(MyCommands))]
```

### 8. Interactive Jig Pattern
```csharp
public class MyJig : EntityJig
{
    private Point3d m_CurrentPos;
    private JigPromptPointOptions m_Opts;

    public MyJig(Entity entity) : base(entity)
    {
        m_Opts = new JigPromptPointOptions("\nSelect point");
        m_Opts.UserInputControls = UserInputControls.Accept3dCoordinates;
    }

    protected override SamplerStatus Sampler(JigPrompts prompts)
    {
        PromptPointResult res = prompts.AcquirePoint(m_Opts);

        if (res.Status == PromptStatus.OK)
        {
            if (m_CurrentPos == res.Value)
                return SamplerStatus.NoChange;

            m_CurrentPos = res.Value;
            return SamplerStatus.OK;
        }

        return SamplerStatus.Cancel;
    }

    protected override bool Update()
    {
        // Update entity based on m_CurrentPos
        ((MyEntity)Entity).Position = m_CurrentPos;
        return true;
    }
}

// Usage
Editor ed = AcadApp.DocumentManager.MdiActiveDocument.Editor;
MyJig jig = new MyJig(entity);
PromptResult result = ed.Drag(jig);
```

### 9. Spec Part Reader Pattern
```csharp
SpecManager specMgr = SpecManager.GetSpecManager();
SpecPartReader reader = specMgr.SelectParts(specName, partType, nominalDiameter);

while (reader.Next())
{
    SpecPart part = reader.Current;

    // Access properties
    object propValue = part.PropValue("PropertyName");
    string type = part.Type;
    NominalDiameter nd = part.NominalDiameter;

    // Check conditions
    if (/* your condition */)
    {
        // Found the part
        break;
    }
}
```

### 10. Equipment and Support Patterns
```csharp
// Equipment
using (EquipmentHelper eqHelper = new EquipmentHelper())
{
    EquipmentType eqType = eqHelper.LoadTemplate(templatePath, out dwgName, out dwgScale);
    Equipment equipment = eqHelper.CreateEquipmentEntity(eqType, dwgName, dwgScale, db,
                                                         out equipPart, out nozzleParts);

    using (PipingObjectAdder adder = new PipingObjectAdder(dlm3d, db))
    {
        adder.Add(equipPart, equipment, nozzleParts);
        tr.AddNewlyCreatedDBObject(equipment, true);
        tr.Commit();
    }
}

// Support
PartSizeProperties supportPart;
Support support = SupportHelper.CreateSupportEntity(supportInfo, db, out supportPart);

// Align support to pipe
SupportHelper.AlignSupport(support, supportPart, false, pipeId, port);

// Add support
using (PipingObjectAdder adder = new PipingObjectAdder(dlm3d, db))
{
    adder.Add(supportPart, support);
    tr.AddNewlyCreatedDBObject(support, true);
    tr.Commit();
}

// Connect support to pipe
SupportHelper.ConnectSupport(supportId, pipeId);
```

---

## Common Pitfalls and Solutions

### Pitfall 1: Forgetting AddNewlyCreatedDBObject
```csharp
// WRONG - Entity won't be added to database
Pipe pipe = new Pipe();
pipe.StartPoint = Point3d.Origin;
// Missing: tr.AddNewlyCreatedDBObject(pipe, true);
tr.Commit();

// RIGHT
Pipe pipe = new Pipe();
pipe.StartPoint = Point3d.Origin;
tr.AddNewlyCreatedDBObject(pipe, true);
tr.Commit();
```

### Pitfall 2: Using ObjectId Outside Transaction
```csharp
// WRONG - ObjectId might be invalid
ObjectId id;
using (Transaction tr = db.TransactionManager.StartTransaction())
{
    Pipe pipe = new Pipe();
    id = pipe.ObjectId;  // ID not yet valid
    tr.Commit();
}

// RIGHT
ObjectId id;
using (Transaction tr = db.TransactionManager.StartTransaction())
{
    Pipe pipe = new Pipe();
    tr.AddNewlyCreatedDBObject(pipe, true);
    id = pipe.ObjectId;  // Now valid
    tr.Commit();
}
// id is valid outside transaction now
```

### Pitfall 3: Not Checking for Null
```csharp
// WRONG
SpecPart part = FetchSpecPart("Valve", names, values);
ObjectId symbolId = cm.GetSymbol(part, db);  // Might throw if part is null

// RIGHT
SpecPart part = FetchSpecPart("Valve", names, values);
if (part != null)
{
    ObjectId symbolId = cm.GetSymbol(part, db);
}
```

### Pitfall 4: Incorrect Port Names
```csharp
// Ports typically use names like:
// "S1", "S2" - Standard ports
// "P1", "P2" - Parametric ports
// Always verify port names by inspecting the part

PortCollection ports = part.GetPorts(PortType.Static);
foreach (Port port in ports)
{
    ed.WriteMessage("\nPort name: " + port.Name);
}
```

---

## Quick Reference: Common Objects

### Piping Entities
- `Pipe` - Pipe segments
- `PipeInlineAsset` - Fittings, valves, flanges
- `Connector` - Welds, gaskets, bolt sets
- `Equipment` - Vessels, tanks, pumps
- `Support` - Pipe supports and hangers

### PnID Entities
- `LineSegment` - Process lines
- `Asset` - Inline equipment, valves
- `EndlineObject` - Line terminations

### Manager Classes
- `SpecManager` - Spec database access
- `ContentManager` - Symbol/block management
- `DataLinksManager` - Property management
- `ConnectionManager` - Port connections
- `ValidationSingleton.Manager` - Validation rules

### Helper Classes
- `PipingObjectAdder` - Add piping objects
- `RoutingHelper` - Routing calculations
- `SupportHelper` - Support operations
- `EquipmentHelper` - Equipment operations
- `PnP3dTagFormat` - Tagging utilities

---

## Example: Complete Pipeline Creation

Here's a complete example that demonstrates method chaining and proper API usage:

```csharp
[CommandMethod("CreatePipelineExample")]
public static void CreatePipelineExample()
{
    Database db = AcadApp.DocumentManager.MdiActiveDocument.Database;
    Editor ed = AcadApp.DocumentManager.MdiActiveDocument.Editor;

    try
    {
        // Setup
        Project currentProject = PlantApp.CurrentProject.ProjectParts["Piping"];
        DataLinksManager dlm = currentProject.DataLinksManager;
        DataLinksManager3d dlm3d = DataLinksManager3d.Get3dManager(dlm);
        ContentManager cm = ContentManager.GetContentManager();

        using (Transaction tr = db.TransactionManager.StartTransaction())
        {
            using (PipingObjectAdder adder = new PipingObjectAdder(dlm3d, db))
            {
                // Create filters
                StringCollection names = new StringCollection();
                StringCollection values = new StringCollection();
                names.Add("NominalDiameter");
                values.Add("6");

                // 1. Create pipe
                SpecPart pipePart = FetchSpecPart("Pipe", names, values);
                Pipe pipe = new Pipe();
                pipe.StartPoint = Point3d.Origin;
                pipe.EndPoint = new Point3d(100, 0, 0);
                pipe.OuterDiameter = (double)pipePart.PropValue("MatchingPipeOd");

                adder.Add(pipePart, pipe);
                ObjectId pipeId = pipe.ObjectId;
                tr.AddNewlyCreatedDBObject(pipe, true);

                // 2. Get next position
                PortCollection pipePorts = pipe.GetPorts(PortType.Static);
                Point3d nextPos = pipePorts[1].Position;

                // 3. Create weld connector
                PartSizePropertiesCollection connProps =
                    FetchConnectorSpecParts(names, values, "Buttweld");
                Connector weld = CreateConnector(connProps, db, cm, currentProject);
                weld.Position = nextPos;
                weld.SetOrientation(new Vector3d(1, 0, 0), new Vector3d(0, 0, 1));

                adder.Add("Buttweld", connProps, weld);
                ObjectId weldId = weld.ObjectId;
                tr.AddNewlyCreatedDBObject(weld, true);

                // 4. Connect pipe and weld
                ConnectParts(pipeId, "S2", weldId, "S1", db, currentProject);

                ed.WriteMessage("\nPipeline created successfully!");
            }

            tr.Commit();
        }
    }
    catch (System.Exception ex)
    {
        ed.WriteMessage("\nError: " + ex.Message);
    }
}
```

---

## Additional Resources

### File Locations
- Spec Files: `C:\ProgramData\Autodesk\C3D 2024\Spec\...`
- Catalog Files: `C:\ProgramData\Autodesk\C3D 2024\Catalogs\...`
- Project Files: User-defined project location

### Key Methods Reference

**SpecManager**:
- `GetSpecManager()` - Get singleton
- `SelectParts(spec, type, nd)` - Query parts
- `HasType(spec, type)` - Check if type exists

**PipingObjectAdder**:
- `Add(specPart, pipe)` - Add pipe
- `Add(specPart, asset)` - Add inline asset
- `Add(connName, propColl, conn)` - Add connector

**ConnectionManager**:
- `Connect(pair1, pair2)` - Connect ports
- `IsConnected(pair)` - Check connection status

**RoutingHelper**:
- `CalculateAttachMatrix()` - Alignment matrix
- `Connect()` - Connect with routing
- `BreakPipeWithAsset()` - Insert asset in pipe

---

This guide provides the foundation for Plant 3D API development. Always refer to the official Autodesk documentation for complete API reference and the latest updates.

**Version**: Based on ObjectARX for Plant 3D 2024
**Last Updated**: 2025
