Imports System
Imports System.Collections.Generic
Imports System.Collections.Specialized

Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.ProcessPower.Validation
Imports Autodesk.ProcessPower.PnIDDwgValidation
Imports Autodesk.ProcessPower.DataLinks
Imports Autodesk.ProcessPower.PlantInstance
Imports Autodesk.ProcessPower.ProjectManager
Imports Autodesk.ProcessPower.PnP3dObjects

Namespace Autodesk.ProcessPower.PipingValidation
    Public Class UnconnectedPortRule
        Inherits DrawingRule
        Implements IAcPpDrawingValidationRule

        Public Sub New()
            MyBase.New(RuleDescription, RuleGuid, RuleName)
        End Sub

        Public Overrides Function GetEnabledFromCurrentProject() As Boolean
            'return GetEnabledFromPipingPart(Me.Guid); 
            Return True
        End Function

        Public Overrides Sub SetEnabledToCurrentProject(bEnabled As Boolean)
            'SetEnabledToPipingPart(Me.Guid, bEnabled); 
        End Sub

        Public Overrides Sub SubEvaluate(dwg As Database)
            If dwg Is Nothing Then
                Return
            End If

            Dim arrAll3dObjIds As ObjectIdCollection = PipingValidationUtils.GetAll3dObjectIds(dwg)
            For Each idPart As ObjectId In arrAll3dObjIds
                Using transaction As Transaction = dwg.TransactionManager.StartTransaction()
                    Dim part As Part = TryCast(transaction.GetObject(idPart, OpenMode.ForRead), Part)
                    If part Is Nothing Then
                        Continue For
                    End If

                    Dim cmgr As New ConnectionManager()
                    If cmgr Is Nothing Then
                        Continue For
                    End If

                    Dim ports As PortCollection = part.GetPorts(PortType.All)
                    For Each port As Port In ports
                        Dim pair As New Pair()
                        pair.ObjectId = idPart
                        pair.Port = port

                        If Not cmgr.IsConnected(pair) Then
                            Dim [error] As New UnconnectedPortError(dwg.FingerprintGuid)
                            [error].DisplayName = "Open port [" & port.Name & "] on component"
                            [error].Description = "The port is not connected to a component."

                            Dim strPartTag As String = PipingValidationUtils.GetTagValue(idPart)
                            If Not String.IsNullOrEmpty(strPartTag) Then
                                [error].DisplayName &= " [" & strPartTag & "]"
                            End If

                            [error].ObjectId = PipingValidationUtils.GetPpObjectId(idPart)
                            [error].Point = port.Position

                            Dim vmgr As AcPpValidationManager = ValidationSingleton.Manager
                            vmgr.Errors.Add([error])
                        End If
                    Next
                End Using
            Next
        End Sub

        Public Shared RuleGuid As String = "Autodesk.ProcessPower.PipingValidation.UnconnectedPortRule"
        Public Shared RuleName As String = "UnconnectedPortRule"
        Public Shared RuleDescription As String = "Unconnected Port Rule"
    End Class

    Public Class UnconnectedPortError
        Inherits DrawingError

        Public Sub New(strDrawingGuid As String)
            MyBase.New(ErrorName, ErrorDiscription, UnconnectedPortRule.RuleGuid, strDrawingGuid)
        End Sub

        Public Overrides ReadOnly Property Details As LinkedList(Of ValidationDetail)
            Get
                Dim properties As New LinkedList(Of ValidationDetail)()
                Dim currentproperty As New ValidationDetail()

                currentproperty.Field = "Error Type"
                currentproperty.Value = "Open port"
                currentproperty.HelperString = "The port is not connected to a component."

                properties.AddLast(currentproperty)

                Return properties
            End Get
        End Property

        Public Shared ErrorName As String = "Open Ports"
        Public Shared ErrorDiscription As String = "Unconnected Port Error"
    End Class

    Public Class PipingValidationUtils
        Public Shared Function GetAll3dObjectIds(dwg As Database) As ObjectIdCollection
            Dim arr3dObjectIds As ObjectIdCollection = Nothing

            Using transaction As Transaction = dwg.TransactionManager.StartTransaction()
                Dim bt As BlockTable = TryCast(transaction.GetObject(dwg.BlockTableId, OpenMode.ForRead), BlockTable)
                If bt IsNot Nothing Then
                    Dim btrModelSpace As BlockTableRecord = TryCast(transaction.GetObject(bt("*Model_Space"), OpenMode.ForRead), BlockTableRecord)
                    If btrModelSpace IsNot Nothing Then
                        arr3dObjectIds = New ObjectIdCollection()

                        Dim btre As BlockTableRecordEnumerator = btrModelSpace.GetEnumerator()
                        While btre.MoveNext()
                            Dim part As Part = TryCast(transaction.GetObject(btre.Current, OpenMode.ForRead), Part)
                            If part IsNot Nothing Then
                                arr3dObjectIds.Add(part.ObjectId)
                            End If
                        End While
                    End If
                End If
            End Using

            Return arr3dObjectIds
        End Function

        Public Shared Function GetTagValue(idPart As ObjectId) As String
            Dim strTagValue As String = Nothing

            strTagValue = GetTag(idPart, "Tag")
            If String.IsNullOrEmpty(strTagValue) Then
                strTagValue = GetTag(idPart, "LineNumberTag")
            End If

            Return strTagValue
        End Function

        Public Shared Function GetPpObjectId(id As ObjectId) As PpObjectId
            Dim ppObjId As New PpObjectId()

            Dim dlmgr As DataLinksManager = GetDataLinksManager()
            If dlmgr IsNot Nothing Then
                ppObjId = dlmgr.MakeAcPpObjectId(id)
            End If

            Return ppObjId
        End Function

        Private Shared Function GetDataLinksManager() As DataLinksManager
            Dim dlmgr As DataLinksManager = Nothing

            Dim prjRoot As PlantProject = PlantApplication.CurrentProject
            Dim prjPiping As Project = prjRoot.ProjectParts("Piping")
            If prjPiping IsNot Nothing AndAlso prjPiping.Isloaded() Then
                dlmgr = prjPiping.DataLinksManager
            End If

            Return dlmgr
        End Function

        Private Shared Function GetTag(id As ObjectId, strTagName As String) As String
            Dim strTag As String = Nothing

            Dim dlmgr As DataLinksManager = GetDataLinksManager()
            If dlmgr IsNot Nothing Then
                Dim arrPropertyNames As New StringCollection()
                arrPropertyNames.Add(strTagName)

                Dim arrPropertyValues As StringCollection = dlmgr.GetProperties(id, arrPropertyNames, True)
                If arrPropertyValues.Count > 0 Then
                    If Not String.IsNullOrEmpty(arrPropertyValues(0)) Then
                        strTag = arrPropertyValues(0)
                    End If
                End If
            End If

            Return strTag
        End Function
    End Class
End Namespace
