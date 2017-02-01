using System;
using System.Threading;
namespace WorkWithTFS
{
    partial class Log
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
        [STAThread]
        private void InitializeComponent()
        {
            this.StatusLogList = new System.Windows.Forms.ListBox();
            this.Ckear = new System.Windows.Forms.Button();
            this.Save = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // StatusLogList
            // 
            this.StatusLogList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StatusLogList.FormattingEnabled = true;
            this.StatusLogList.Location = new System.Drawing.Point(-1, 4);
            this.StatusLogList.Name = "StatusLogList";
            this.StatusLogList.Size = new System.Drawing.Size(898, 394);
            this.StatusLogList.TabIndex = 0;
            // 
            // Ckear
            // 
            this.Ckear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Ckear.AutoSize = true;
            this.Ckear.Location = new System.Drawing.Point(3, 403);
            this.Ckear.Name = "Ckear";
            this.Ckear.Size = new System.Drawing.Size(65, 24);
            this.Ckear.TabIndex = 1;
            this.Ckear.Text = "Очистить";
            this.Ckear.UseVisualStyleBackColor = true;
            this.Ckear.Click += new System.EventHandler(this.Ckear_Click);
            // 
            // Save
            // 
            this.Save.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Save.Location = new System.Drawing.Point(74, 403);
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size(72, 24);
            this.Save.TabIndex = 1;
            this.Save.Text = "Сохранить";
            this.Save.UseVisualStyleBackColor = true;
            this.Save.Click += new System.EventHandler(this.Save_Click);
            // 
            // Log
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(897, 429);
            this.Controls.Add(this.Save);
            this.Controls.Add(this.Ckear);
            this.Controls.Add(this.StatusLogList);
            this.Name = "Log";
            this.Text = "История строки статуса";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.ListBox StatusLogList;
        private System.Windows.Forms.Button Ckear;
        private System.Windows.Forms.Button Save;
    }
}