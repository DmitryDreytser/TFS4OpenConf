namespace WorkWithTFS
{
    partial class TreeForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TreeForm));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbExpandAll = new System.Windows.Forms.ToolStripButton();
            this.tsbCollapsAll = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnAddFolder = new System.Windows.Forms.Button();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnSelect = new System.Windows.Forms.Button();
            this.tree = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.pnlFilter = new System.Windows.Forms.Panel();
            this.txbFilter = new System.Windows.Forms.TextBox();
            this.btnClearFilter = new System.Windows.Forms.Button();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.pnlFilter.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbExpandAll,
            this.tsbCollapsAll,
            this.toolStripButton1});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(492, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbExpandAll
            // 
            this.tsbExpandAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbExpandAll.Image = global::WorkWithTFS.Properties.Resources.Expand;
            this.tsbExpandAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExpandAll.Name = "tsbExpandAll";
            this.tsbExpandAll.Size = new System.Drawing.Size(23, 22);
            this.tsbExpandAll.Text = "Раскрыть все";
            this.tsbExpandAll.Click += new System.EventHandler(this.tsbExpandAll_Click);
            // 
            // tsbCollapsAll
            // 
            this.tsbCollapsAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbCollapsAll.Image = global::WorkWithTFS.Properties.Resources.Collapse;
            this.tsbCollapsAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbCollapsAll.Name = "tsbCollapsAll";
            this.tsbCollapsAll.Size = new System.Drawing.Size(23, 22);
            this.tsbCollapsAll.Text = "Свернуть все узлы";
            this.tsbCollapsAll.Click += new System.EventHandler(this.tsbCollapsAll_Click);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = global::WorkWithTFS.Properties.Resources.FolderCollapsed1;
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "Добавить каталог";
            this.toolStripButton1.Click += new System.EventHandler(this.btnAddFolder_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.btnAddFolder);
            this.panel1.Controls.Add(this.btnRefresh);
            this.panel1.Controls.Add(this.btnCancel);
            this.panel1.Controls.Add(this.btnSelect);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel1.Location = new System.Drawing.Point(351, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(141, 477);
            this.panel1.TabIndex = 1;
            // 
            // btnAddFolder
            // 
            this.btnAddFolder.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnAddFolder.Location = new System.Drawing.Point(6, 61);
            this.btnAddFolder.Name = "btnAddFolder";
            this.btnAddFolder.Size = new System.Drawing.Size(128, 23);
            this.btnAddFolder.TabIndex = 3;
            this.btnAddFolder.Text = "Добавить каталог";
            this.btnAddFolder.UseVisualStyleBackColor = true;
            this.btnAddFolder.Click += new System.EventHandler(this.btnAddFolder_Click);
            // 
            // btnRefresh
            // 
            this.btnRefresh.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRefresh.Location = new System.Drawing.Point(6, 32);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(128, 23);
            this.btnRefresh.TabIndex = 2;
            this.btnRefresh.Text = "Обновить";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCancel.Location = new System.Drawing.Point(6, 158);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(128, 23);
            this.btnCancel.TabIndex = 1;
            this.btnCancel.Text = "Отмена";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnSelect
            // 
            this.btnSelect.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnSelect.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSelect.Location = new System.Drawing.Point(6, 3);
            this.btnSelect.Name = "btnSelect";
            this.btnSelect.Size = new System.Drawing.Size(128, 23);
            this.btnSelect.TabIndex = 0;
            this.btnSelect.Text = "Выбрать";
            this.btnSelect.UseVisualStyleBackColor = true;
            this.btnSelect.Click += new System.EventHandler(this.btnSelect_Click);
            // 
            // tree
            // 
            this.tree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tree.HideSelection = false;
            this.tree.ImageIndex = 0;
            this.tree.ImageList = this.imageList1;
            this.tree.ItemHeight = 16;
            this.tree.LabelEdit = true;
            this.tree.Location = new System.Drawing.Point(0, 25);
            this.tree.Name = "tree";
            this.tree.SelectedImageIndex = 0;
            this.tree.ShowNodeToolTips = true;
            this.tree.Size = new System.Drawing.Size(351, 457);
            this.tree.StateImageList = this.imageList1;
            this.tree.TabIndex = 2;
            this.tree.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.tree_BeforeLabelEdit);
            this.tree.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.tree_AfterLabelEdit);
            this.tree.DoubleClick += new System.EventHandler(this.tree_DoubleClick);
            this.tree.MouseUp += new System.Windows.Forms.MouseEventHandler(this.tree_MouseUp);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "FolderCollapsed.ico");
            this.imageList1.Images.SetKeyName(1, "FolderUncollapsed.ico");
            this.imageList1.Images.SetKeyName(2, "Processing.ico");
            this.imageList1.Images.SetKeyName(3, "file.ico");
            this.imageList1.Images.SetKeyName(4, "Collapse.png");
            this.imageList1.Images.SetKeyName(5, "Expand.png");
            // 
            // pnlFilter
            // 
            this.pnlFilter.Controls.Add(this.txbFilter);
            this.pnlFilter.Controls.Add(this.btnClearFilter);
            this.pnlFilter.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlFilter.Location = new System.Drawing.Point(0, 482);
            this.pnlFilter.Name = "pnlFilter";
            this.pnlFilter.Size = new System.Drawing.Size(351, 20);
            this.pnlFilter.TabIndex = 4;
            // 
            // txbFilter
            // 
            this.txbFilter.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbFilter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txbFilter.Location = new System.Drawing.Point(0, 0);
            this.txbFilter.MaxLength = 255;
            this.txbFilter.Name = "txbFilter";
            this.txbFilter.Size = new System.Drawing.Size(331, 20);
            this.txbFilter.TabIndex = 0;
            this.txbFilter.TextChanged += new System.EventHandler(this.txbFilter_TextChanged);
            // 
            // btnClearFilter
            // 
            this.btnClearFilter.BackColor = System.Drawing.SystemColors.Control;
            this.btnClearFilter.Dock = System.Windows.Forms.DockStyle.Right;
            this.btnClearFilter.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnClearFilter.ForeColor = System.Drawing.SystemColors.ControlText;
            this.btnClearFilter.Location = new System.Drawing.Point(331, 0);
            this.btnClearFilter.Name = "btnClearFilter";
            this.btnClearFilter.Size = new System.Drawing.Size(20, 20);
            this.btnClearFilter.TabIndex = 1;
            this.btnClearFilter.Text = "X";
            this.btnClearFilter.UseVisualStyleBackColor = false;
            this.btnClearFilter.Click += new System.EventHandler(this.btnClearFilter_Click);
            // 
            // TreeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(492, 502);
            this.Controls.Add(this.tree);
            this.Controls.Add(this.pnlFilter);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "TreeForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Load += new System.EventHandler(this.TreeForm_Load);
            this.Shown += new System.EventHandler(this.TreeForm_Shown);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.pnlFilter.ResumeLayout(false);
            this.pnlFilter.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnSelect;
        private System.Windows.Forms.TreeView tree;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.Button btnAddFolder;
        private System.Windows.Forms.Panel pnlFilter;
        private System.Windows.Forms.TextBox txbFilter;
        private System.Windows.Forms.Button btnClearFilter;
        private System.Windows.Forms.ToolStripButton tsbExpandAll;
        private System.Windows.Forms.ToolStripButton tsbCollapsAll;
    }
}