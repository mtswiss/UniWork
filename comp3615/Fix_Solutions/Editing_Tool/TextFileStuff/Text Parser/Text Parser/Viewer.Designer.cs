namespace Text_Parser
{
    partial class Viewer
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TextDataGrid = new System.Windows.Forms.DataGridView();
            this.day = new System.Windows.Forms.TextBox();
            this.trip1 = new System.Windows.Forms.TextBox();
            this.trip2 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.deleteTrip = new System.Windows.Forms.Button();
            this.joinTrip = new System.Windows.Forms.Button();
            this.splitTrip = new System.Windows.Forms.Button();
            this.undoTrip = new System.Windows.Forms.Button();
            this.undoTableView = new System.Windows.Forms.DataGridView();
            this.undoTypeTableView = new System.Windows.Forms.DataGridView();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.TextDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.undoTableView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.undoTypeTableView)).BeginInit();
            this.SuspendLayout();
            // 
            // TextDataGrid
            // 
            this.TextDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.TextDataGrid.Location = new System.Drawing.Point(12, 69);
            this.TextDataGrid.Name = "TextDataGrid";
            this.TextDataGrid.Size = new System.Drawing.Size(419, 233);
            this.TextDataGrid.TabIndex = 0;
            // 
            // day
            // 
            this.day.Location = new System.Drawing.Point(14, 43);
            this.day.Name = "day";
            this.day.Size = new System.Drawing.Size(47, 20);
            this.day.TabIndex = 1;
            this.day.TextChanged += new System.EventHandler(this.day_TextChanged);
            // 
            // trip1
            // 
            this.trip1.Location = new System.Drawing.Point(88, 43);
            this.trip1.Name = "trip1";
            this.trip1.Size = new System.Drawing.Size(47, 20);
            this.trip1.TabIndex = 2;
            this.trip1.TextChanged += new System.EventHandler(this.trip1_TextChanged);
            // 
            // trip2
            // 
            this.trip2.Location = new System.Drawing.Point(160, 43);
            this.trip2.Name = "trip2";
            this.trip2.Size = new System.Drawing.Size(47, 20);
            this.trip2.TabIndex = 3;
            this.trip2.TextChanged += new System.EventHandler(this.trip2_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(26, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Day";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(92, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Trip 1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(165, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(34, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Trip 2";
            // 
            // deleteTrip
            // 
            this.deleteTrip.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.deleteTrip.Location = new System.Drawing.Point(14, 311);
            this.deleteTrip.Name = "deleteTrip";
            this.deleteTrip.Size = new System.Drawing.Size(89, 27);
            this.deleteTrip.TabIndex = 7;
            this.deleteTrip.Text = "Delete Trip";
            this.deleteTrip.UseVisualStyleBackColor = true;
            this.deleteTrip.Click += new System.EventHandler(this.deleteTrip_Click);
            // 
            // joinTrip
            // 
            this.joinTrip.Location = new System.Drawing.Point(131, 311);
            this.joinTrip.Name = "joinTrip";
            this.joinTrip.Size = new System.Drawing.Size(89, 27);
            this.joinTrip.TabIndex = 8;
            this.joinTrip.Text = "Join Trip";
            this.joinTrip.UseVisualStyleBackColor = true;
            this.joinTrip.Click += new System.EventHandler(this.joinTrip_Click);
            // 
            // splitTrip
            // 
            this.splitTrip.Location = new System.Drawing.Point(245, 311);
            this.splitTrip.Name = "splitTrip";
            this.splitTrip.Size = new System.Drawing.Size(89, 27);
            this.splitTrip.TabIndex = 9;
            this.splitTrip.Text = "Split Trip";
            this.splitTrip.UseVisualStyleBackColor = true;
            // 
            // undoTrip
            // 
            this.undoTrip.Location = new System.Drawing.Point(245, 36);
            this.undoTrip.Name = "undoTrip";
            this.undoTrip.Size = new System.Drawing.Size(89, 27);
            this.undoTrip.TabIndex = 10;
            this.undoTrip.Text = "Undo";
            this.undoTrip.UseVisualStyleBackColor = true;
            this.undoTrip.Click += new System.EventHandler(this.undoTrip_Click);
            // 
            // undoTableView
            // 
            this.undoTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.undoTableView.Location = new System.Drawing.Point(462, 69);
            this.undoTableView.Name = "undoTableView";
            this.undoTableView.Size = new System.Drawing.Size(240, 233);
            this.undoTableView.TabIndex = 11;
            // 
            // undoTypeTableView
            // 
            this.undoTypeTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.undoTypeTableView.Location = new System.Drawing.Point(742, 69);
            this.undoTypeTableView.Name = "undoTypeTableView";
            this.undoTypeTableView.Size = new System.Drawing.Size(240, 233);
            this.undoTypeTableView.TabIndex = 12;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(459, 335);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "label4";
            // 
            // Viewer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 446);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.undoTypeTableView);
            this.Controls.Add(this.undoTableView);
            this.Controls.Add(this.undoTrip);
            this.Controls.Add(this.splitTrip);
            this.Controls.Add(this.joinTrip);
            this.Controls.Add(this.deleteTrip);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trip2);
            this.Controls.Add(this.trip1);
            this.Controls.Add(this.day);
            this.Controls.Add(this.TextDataGrid);
            this.Name = "Viewer";
            this.Text = "Viewer";
            ((System.ComponentModel.ISupportInitialize)(this.TextDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.undoTableView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.undoTypeTableView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView TextDataGrid;
        private System.Windows.Forms.TextBox day;
        private System.Windows.Forms.TextBox trip1;
        private System.Windows.Forms.TextBox trip2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button deleteTrip;
        private System.Windows.Forms.Button joinTrip;
        private System.Windows.Forms.Button splitTrip;
        private System.Windows.Forms.Button undoTrip;
        private System.Windows.Forms.DataGridView undoTableView;
        private System.Windows.Forms.DataGridView undoTypeTableView;
        private System.Windows.Forms.Label label4;
    }
}