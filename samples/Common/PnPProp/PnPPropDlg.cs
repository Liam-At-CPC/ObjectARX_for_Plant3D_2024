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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;



namespace Properties
{
    public partial class PropertyDialog : Form
    {
        private String textVal;
        private String textName;
        private int startHeight;
        private int startWidth;

        /// <summary>
        /// Display tooltips on various items in the dialog box. 
        /// </summary>
        private void DisplayToolTips()
        {
            System.Windows.Forms.ToolTip toolTip = new System.Windows.Forms.ToolTip();
            // Set up the delays for the ToolTip.
            toolTip.AutoPopDelay = 5000;
            toolTip.InitialDelay = 1000;
            toolTip.ReshowDelay = 500;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTip.ShowAlways = true;

            toolTip.SetToolTip(this.selectBtn, "Select Object");
            toolTip.SetToolTip(this.clearBtn, "Clear Text");
            toolTip.SetToolTip(this.updateBtn, "Update Value");
            toolTip.SetToolTip(this.closeBtn, "Close Window");
        }

        public PropertyDialog()
        {
            InitializeComponent();
            startHeight = this.Height;
            startWidth = this.Width;
            DisplayToolTips();
         }
        /// <summary>
        /// Adds a row to the datagrid
        /// </summary>
        /// <param name="row">String to be displayed in the added row</param>
        public void AddRowDataGrid(String[] row)
        {
            this.dataGridView.Rows.Add(row);
        }

        /// <summary>
        /// Clears datagrid table
        /// </summary>
        public void ClearDataGrid()
        {
            this.dataGridView.Rows.Clear();
        }

        /// <summary>
        /// This function is called when the update button(button with the green arrow) is clicked
        /// </summary>
        private void updateBtn_Click(object sender, EventArgs e)
        {
            String newVal = this.textBox.Text;

            if (newVal != textVal)
            {
                if (textVal != null)
                {
                    Properties.Property.UpdateProperty(textName, textVal, newVal);

                    DataGridViewRow row = this.dataGridView.CurrentRow;

                    row.Cells[1].Value = newVal;
                    row.Cells[1].ToolTipText = newVal;
                    this.textBox.ForeColor = System.Drawing.Color.Black;
                    textVal = newVal;
                }
                else
                    MessageBox.Show("Update canceled"); 
            }
            else
                MessageBox.Show("Value not updated. Command canceled"); 
        }

        /// <summary>
        /// This function is called when selection of any particular row is changed. It updates the textBox accordingly. 
        /// </summary>
        private void dataGridView_SelectionChanged(object sender, EventArgs e)
        {
            this.textBox.ForeColor = System.Drawing.Color.Black;
            if (this.dataGridView.CurrentRow != null)
            {
                DataGridViewRow row = this.dataGridView.CurrentRow;
                textVal = (String)row.Cells[1].Value;
                textName = (String)row.Cells[0].Value;
                this.textBox.Text = textVal;
                this.textBox.Visible = true;

            }
            else
            {
                DataGridViewRow row = this.dataGridView.Rows[0];
                textVal = (String)row.Cells[1].Value;
                textName = (String)row.Cells[0].Value;
                this.textBox.Text = textVal;
                this.textBox.Visible = true;

            }
        }

        /// <summary>
        /// Called when any row in the datagrid is double clicked. 
        /// Note that an empty "Value" cell is not responsive to the double click. 
        /// </summary>
        void dataGridView_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
           this.textBox.Focus(); 
        }

        /// <summary>
        /// Called when any key is pressed when the focus is on the property dialog. 
        /// </summary>
        private void PropDlg_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                this.Close();
            }
        }

        /// <summary>
        /// Called when select button is pressed. 
        /// The dialog is made invisible and prompts user to select an object on the scereen. 
        /// </summary>
        private void selectBtn_Click(object sender, EventArgs e)
        {
            Properties.Property.GetPropertyDialog().Visible = false;
            Properties.Property.RunPropertyCommand();
            foreach (DataGridViewRow row in this.dataGridView.Rows)
            {
                row.Cells[0].ToolTipText = (String)row.Cells[0].Value;
                row.Cells[1].ToolTipText = (String)row.Cells[1].Value;
            }
        }

        /// <summary>
        /// Called when "Close" button is pressed. Closes the dialog. 
        /// </summary>
        private void closeBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// This function is called when any key is pressed, the focus being on the textbox item. 
        /// It updates the value entered only if the user presses the Enter key. 
        /// </summary>
        private void textBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                updateBtn_Click(sender, e);
        }

        /// <summary>
        /// This function is called when the focus is brought to the textBox item. 
        /// It is used to enable/disable the update button. No point having the update button clickable when nothing has been entered in the texbox field. 
        /// </summary>
        private void textBox_Enter(object sender, EventArgs e)
        {
            if (this.textBox.Text.Length != 0 )
                this.updateBtn.Enabled = true;
            else
                this.updateBtn.Enabled = false;            
        }

        /// <summary>
        /// Clears everything that is entered in the textbox field. 
        /// It doesnt update the value until update button is clicked. 
        /// </summary>
        private void clearBtn_Click(object sender, EventArgs e)
        {
            this.textBox.Clear();             
        }

        /// <summary>
        /// Called when the property dialog box is changed in size. 
        /// </summary>
        private void PropertyDialog_SizeChanged(object sender, EventArgs e)
        {
            this.dataGridView.Height += this.Height - startHeight;
            this.dataGridView.Width += this.Width - startWidth;
            this.NameColumn.Width = (this.dataGridView.Width - 43) / 2;
            this.Value.Width = this.NameColumn.Width;
            this.textBox.Width += this.Width - startWidth;
            this.clearBtn.Location = new System.Drawing.Point(this.clearBtn.Location.X + this.Width - startWidth, this.clearBtn.Location.Y);
            this.closeBtn.Location = new System.Drawing.Point(this.closeBtn.Location.X + this.Width - startWidth, this.closeBtn.Location.Y);
            this.updateBtn.Location = new System.Drawing.Point(this.updateBtn.Location.X + this.Width - startWidth, this.updateBtn.Location.Y);
            startWidth = this.Width;
            startHeight = this.Height;
        }

        /// <summary>
        /// Called when user inputs text in the textBox field. 
        /// If the old text is edited, the text is displayed in red colour. Otherwise it is in black. 
        /// </summary>
        private void textBox_TextChanged(object sender, EventArgs e)
        {
            if ((this.textBox.Text != textVal) && !(textVal == null))
            {
                if(!(textVal.Equals(""))) 
                    this.textBox.ForeColor = System.Drawing.Color.Red;
            }
            else
                this.textBox.ForeColor = System.Drawing.Color.Black;

            this.updateBtn.Enabled = true;                        
        }


    }
}