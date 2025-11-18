//
// (C) Copyright 2009 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Windows.Forms;

using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.EditorInput; 
using AcadApp = Autodesk.AutoCAD.ApplicationServices.Application;


[assembly: ExtensionApplication(typeof(Properties.ExtApp))]
[assembly: CommandClass(typeof(Properties.Property))]





namespace Properties
{
    public class ExtApp : IExtensionApplication
    {
        public void Initialize()
        {

        }
        public void Terminate()
        {

        }
    }
    public class Property
    {
        static PropertyDialog propDlg;
        static ObjectId objId;
        static Autodesk.ProcessPower.DataLinks.DataLinksManager dlObj;
        static Database oDatabase;//= AcadApp.DocumentManager.MdiActiveDocument.Database;
        static Editor oEditor;//= AcadApp.DocumentManager.MdiActiveDocument.Editor;
        static List<KeyValuePair<string, string>> listProp;

        /// <summary>
        /// Returns an instance of Property Dialog
        /// </summary>
        public static PropertyDialog GetPropertyDialog() { return propDlg; }

        // Set the active environment
        public static void setWorkingEnvironment()
        {
            oDatabase = AcadApp.DocumentManager.MdiActiveDocument.Database;
            oEditor = AcadApp.DocumentManager.MdiActiveDocument.Editor;
        }

        /// <summary>
        /// Updates the property, as entered by the user, in the Datalinks manager.
        /// </summary>
        public static void UpdateProperty(String txtName, String txtOldVal, String txtNewVal)
        {
            Transaction oTransaction = null;
            try
            {
                using (oTransaction = oDatabase.TransactionManager.StartTransaction())
                {
                    KeyValuePair<string, string> oldVal = new KeyValuePair<string, string>(txtName, txtOldVal);
                    KeyValuePair<string, string> newVal = new KeyValuePair<string, string>(txtName, txtNewVal);
                    listProp.Remove(oldVal);
                    listProp.Add(newVal);
                    System.Collections.Specialized.StringCollection strNames = new System.Collections.Specialized.StringCollection();
                    System.Collections.Specialized.StringCollection strValues = new System.Collections.Specialized.StringCollection();
                    for (int i = 0; i < listProp.Count; i++)
                    {
                        String name = listProp[i].Key;
                        String value = listProp[i].Value;
                        strNames.Add(name);
                        strValues.Add(value);
                    }
                    dlObj.SetProperties(objId, strNames, strValues);
                    oTransaction.Commit();
                }
            }
            catch (System.Exception e)
            {
                if (oTransaction != null)
                {
                    oTransaction.Abort();
                    oTransaction.Dispose();
                }
                MessageBox.Show(e.Message.ToString());
            }
        }

        /// <summary>
        /// This function is called when the command is executed. If the user has already selected objects, 
        /// then upon running, the properties of the selected object are displayed. 
        /// Incase of more than one selection, the first object selected is used. 
        /// </summary>
        [CommandMethod("PNPPROP", CommandFlags.Redraw | CommandFlags.UsePickSet)]
        public static void InitialDialog()
        {
            // Set the environment to the current active database and editor when the command execute
            setWorkingEnvironment();

            PromptSelectionResult selResult = oEditor.SelectImplied();
            SelectionSet selSet = selResult.Value;
            if (selSet != null)
            {
                ObjectId[] objIds = selSet.GetObjectIds();
                if (objIds != null)
                {
                    propDlg = new PropertyDialog();
                    if (objIds.Length > 1)
                        oEditor.WriteMessage("\n More than one objects selected. Properties of the first object will be displayed."); 
                    ObjectId objId = objIds[0];
                    PickFirstSelection_LoadDialog(objId);
                    propDlg.Visible = true;
                }
            }
            else
            {
                propDlg = new PropertyDialog();
                Autodesk.AutoCAD.ApplicationServices.Application.ShowModalDialog(propDlg);
            }
        }

        /// <summary>
        /// Prompts user to select the object. Brings up the dialog upon selection. 
        /// Populates the datagrid table with the object properties.
        /// </summary>
        public static void RunPropertyCommand()
        {
            Transaction oTransaction = null;
            try
            {              
                PromptEntityOptions oPromptOptions = new PromptEntityOptions("Select an object");                
                PromptEntityResult oPromptResult = oEditor.GetEntity(oPromptOptions);

                if (oPromptResult.Status != PromptStatus.OK)
                {
                    propDlg.Visible = true;
                    return;
                }

                using (oTransaction = oDatabase.TransactionManager.StartTransaction())
                {
                    DBObject obj = oTransaction.GetObject(oPromptResult.ObjectId, OpenMode.ForRead);
                    objId = obj.ObjectId;
                    System.Collections.Specialized.StringCollection strColl = Autodesk.ProcessPower.DataLinks.DataLinksManager.GetLinkManagerNames();
                    if (strColl.Count > 0)
                    {
                        String dlName = strColl[0];

                        if (dlName != String.Empty)
                        {
                            dlObj = Autodesk.ProcessPower.DataLinks.DataLinksManager.GetManager(dlName);

                            if (dlObj != null)
                            {
                                try
                                {
                                    listProp = dlObj.GetAllProperties(objId, true);
                                    propDlg.ClearDataGrid();
                                    String[] row = new String[2];

                                    for (int i = 0; i < listProp.Count; i++)
                                    {
                                        row[0] = listProp[i].Key;
                                        row[1] = listProp[i].Value;
                                        propDlg.AddRowDataGrid(row);
                                    }
                                    listProp.Clear();
                                    oTransaction.Commit();
                                    propDlg.Visible = true;
                                }
                                catch (System.Exception e)
                                {
                                    if (e.GetType().ToString() == "Autodesk.ProcessPower.DataLinks.DLException")
                                    {
                                        if (oTransaction != null)
                                        {
                                            oTransaction.Abort();
                                            oTransaction.Dispose();
                                        }
                                        MessageBox.Show("Please select a P&ID object.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                        RunPropertyCommand();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (System.Exception e)
            {
                if (oTransaction != null)
                {
                    oTransaction.Abort();
                    oTransaction.Dispose();
                }
                MessageBox.Show(e.Message.ToString());
            }

        }


        /// <summary>
        /// This function is called if the command is run after the user has selected an object or objects. 
        /// It populates the datagrid table with the properties of the object selected. 
        /// Incase of more than one objects, properties of the first object selected are displayed. 
        /// </summary>
        public static void PickFirstSelection_LoadDialog(ObjectId objId)
        {
            Transaction oTransaction = null;
            try
            {
                oDatabase = AcadApp.DocumentManager.MdiActiveDocument.Database;
                using (oTransaction = oDatabase.TransactionManager.StartTransaction())
                {
                    System.Collections.Specialized.StringCollection strColl = Autodesk.ProcessPower.DataLinks.DataLinksManager.GetLinkManagerNames();
                    if (strColl.Count > 0)
                    {
                        String dlName = strColl[0];

                        if (dlName != String.Empty)
                        {
                            dlObj = Autodesk.ProcessPower.DataLinks.DataLinksManager.GetManager(dlName);

                            if (dlObj != null)
                            {
                                try
                                {
                                    listProp = dlObj.GetAllProperties(objId, true);
                                    propDlg.ClearDataGrid();
                                    String[] row = new String[2];

                                    for (int i = 0; i < listProp.Count; i++)
                                    {
                                        row[0] = listProp[i].Key;
                                        row[1] = listProp[i].Value;
                                        propDlg.AddRowDataGrid(row);
                                    }
                                    listProp.Clear();
                                    oTransaction.Commit();
                                    propDlg.Visible = true;
                                }
                                catch (System.Exception e)
                                {
                                    if (e.GetType().ToString() == "Autodesk.ProcessPower.DataLinks.DLException")
                                    {
                                        if (oTransaction != null)
                                        {
                                            oTransaction.Abort();
                                            oTransaction.Dispose();
                                        }
                                    }
                                }
                            }
                        }
                    }

                }

            }
            catch (System.Exception e)
            {
                if (oTransaction != null)
                {
                    oTransaction.Abort();
                    oTransaction.Dispose();
                }
                MessageBox.Show(e.Message.ToString());
            }

        }
    }

}



