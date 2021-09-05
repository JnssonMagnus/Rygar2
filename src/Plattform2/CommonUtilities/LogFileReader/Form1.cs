using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LogFileReader
{
    public partial class Form1 : Form
    {
        private List<List<String>> myTexts;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SelectLogPath();
        }

        private void SelectLogPath()
        {
            folderBrowserDialog1.SelectedPath = Properties.Settings.Default.DialogPath;
            DialogResult result = folderBrowserDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                LogFolderText.Text = folderBrowserDialog1.SelectedPath;
            }

            Properties.Settings.Default.DialogPath = folderBrowserDialog1.SelectedPath;
            Properties.Settings.Default.Save();

            LogPathUpdated();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            myTexts = new List<List<string>>();
            folderBrowserDialog1.SelectedPath = Properties.Settings.Default.DialogPath;
            LogFolderText.Text = folderBrowserDialog1.SelectedPath;
            LogPathUpdated();
        }

        private void LogPathUpdated()
        {
            LogTabControl.TabPages.Clear();
            try
            {
                string[] files = System.IO.Directory.GetFiles(LogFolderText.Text);
                foreach (string fileName in files)
                {
                    int logTextIndex = fileName.IndexOf("_log");
                    if (logTextIndex != -1)
                    {
                        myTexts.Add(new List<string>());
                        string tabName = fileName.Substring(fileName.LastIndexOf("\\") + 1, logTextIndex - fileName.LastIndexOf("\\") - 1);
                        LogTabControl.TabPages.Add(tabName);
                        TabPage newTab = LogTabControl.TabPages[LogTabControl.TabCount - 1];

                        ListBox logText = new ListBox();
                        logText.Name = "TabListBox";
                        logText.Width = newTab.Width;
                        logText.Height = newTab.Height;
                        logText.HorizontalScrollbar = true;
                        logText.SelectionMode = SelectionMode.None;                        

                        string[] lines = System.IO.File.ReadAllLines(fileName);
                        foreach (string line in lines)
                        {
                            myTexts[myTexts.Count - 1].Add(line);
                        }

                        newTab.Controls.Add(logText);
                    }
                }

                ShowAndFilterText();
            }
            catch
            {
                SelectLogPath();
            }
        }

        private void SearchTextField_TextChanged(object sender, EventArgs e)
        {
            ShowAndFilterText();
        }

        private void ShowAndFilterText()
        {
            if (LogTabControl.SelectedTab != null)
            {
                ListBox listBox = (ListBox)this.LogTabControl.SelectedTab.Controls[0];
                listBox.Items.Clear();
                int tabIndex = LogTabControl.SelectedIndex;
                foreach (string text in myTexts[tabIndex])
                {
                    if (text.Contains(SearchTextField.Text) == true)
                    {
                        listBox.Items.Add(text);
                    }
                }
            }
        }

        private void LogTabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            ShowAndFilterText();
        }
    }
}
