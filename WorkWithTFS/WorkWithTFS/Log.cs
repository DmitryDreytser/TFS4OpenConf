using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Collections;
using System.IO;

namespace WorkWithTFS
{
    
    public partial class Log : Form
    {
       
        public Log()
        {
            InitializeComponent();
        }

        public void Update(ArrayList Objects)
        {
            if (Objects.Count > StatusLogList.Items.Count)
            {
                StatusLogList.Items.Add(Objects.ToArray().Last());
                StatusLogList.SelectedIndex = StatusLogList.Items.Count - 1;
            }
        }

        public void Update(string Obj)
        {
            //            if(!StatusLogList.Items.Contains(Obj))
            StatusLogList.BeginUpdate();
            StatusLogList.Items.Add(Obj);
            StatusLogList.SelectedIndex = StatusLogList.Items.Count - 1;
            StatusLogList.EndUpdate();
        }

        static FileDialog SD = new SaveFileDialog() { Filter = "Text files | *.txt", RestoreDirectory = true };

       
        public void SaveLog(string FileName = null)
        {
            if(string.IsNullOrEmpty(FileName))
            {
                if(SD.ShowDialog() == DialogResult.OK)
                    FileName = SD.FileName;

                if (string.IsNullOrEmpty(FileName))
                        return;
            }

            File.WriteAllLines(FileName, StatusLogList.Items.OfType<string>().ToArray());

        }

        
        private void Save_Click(object sender, EventArgs e)
        {
            SaveLog();
        }

        public void Ckear_Click(object sender, EventArgs e)
        {
            StatusLogList.Items.Clear();
        }
    }
}
