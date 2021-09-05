namespace LogFileReader
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.SearchTextField = new System.Windows.Forms.TextBox();
            this.LogTabControl = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.label2 = new System.Windows.Forms.Label();
            this.LogFolderText = new System.Windows.Forms.Label();
            this.ChoseLogPathButton = new System.Windows.Forms.Button();
            this.LogTabControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Search";
            // 
            // SearchTextField
            // 
            this.SearchTextField.Location = new System.Drawing.Point(56, 43);
            this.SearchTextField.Name = "SearchTextField";
            this.SearchTextField.Size = new System.Drawing.Size(175, 20);
            this.SearchTextField.TabIndex = 1;
            this.SearchTextField.TextChanged += new System.EventHandler(this.SearchTextField_TextChanged);
            // 
            // LogTabControl
            // 
            this.LogTabControl.Controls.Add(this.tabPage1);
            this.LogTabControl.Controls.Add(this.tabPage2);
            this.LogTabControl.ItemSize = new System.Drawing.Size(70, 18);
            this.LogTabControl.Location = new System.Drawing.Point(12, 80);
            this.LogTabControl.Name = "LogTabControl";
            this.LogTabControl.SelectedIndex = 0;
            this.LogTabControl.Size = new System.Drawing.Size(623, 421);
            this.LogTabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.LogTabControl.TabIndex = 2;
            this.LogTabControl.SelectedIndexChanged += new System.EventHandler(this.LogTabControl_SelectedIndexChanged);
            // 
            // tabPage1
            // 
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(615, 395);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(615, 395);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2sdfdsfdsdsfsdf";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(41, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Current log folder";
            // 
            // LogFolderText
            // 
            this.LogFolderText.AutoSize = true;
            this.LogFolderText.Location = new System.Drawing.Point(125, 17);
            this.LogFolderText.Name = "LogFolderText";
            this.LogFolderText.Size = new System.Drawing.Size(106, 13);
            this.LogFolderText.TabIndex = 4;
            this.LogFolderText.Text = "LOGFOLDER_TEXT";
            // 
            // ChoseLogPathButton
            // 
            this.ChoseLogPathButton.Location = new System.Drawing.Point(12, 12);
            this.ChoseLogPathButton.Name = "ChoseLogPathButton";
            this.ChoseLogPathButton.Size = new System.Drawing.Size(23, 23);
            this.ChoseLogPathButton.TabIndex = 5;
            this.ChoseLogPathButton.Text = "...";
            this.ChoseLogPathButton.UseVisualStyleBackColor = true;
            this.ChoseLogPathButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(643, 513);
            this.Controls.Add(this.ChoseLogPathButton);
            this.Controls.Add(this.LogFolderText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.LogTabControl);
            this.Controls.Add(this.SearchTextField);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "LogFileViewer";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.LogTabControl.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox SearchTextField;
        private System.Windows.Forms.TabControl LogTabControl;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label LogFolderText;
        private System.Windows.Forms.Button ChoseLogPathButton;
    }
}

