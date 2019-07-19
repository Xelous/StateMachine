namespace SMGen
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
            this.mStateMachines = new System.Windows.Forms.ListBox();
            this.mStateMachinesLabel = new System.Windows.Forms.Label();
            this.mAddStateMachineButton = new System.Windows.Forms.Button();
            this.mDeleteStateMachineButton = new System.Windows.Forms.Button();
            this.mDeleteStateButton = new System.Windows.Forms.Button();
            this.mAddStateButton = new System.Windows.Forms.Button();
            this.mStatesLabel = new System.Windows.Forms.Label();
            this.mStates = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // mStateMachines
            // 
            this.mStateMachines.FormattingEnabled = true;
            this.mStateMachines.Location = new System.Drawing.Point(2, 24);
            this.mStateMachines.Name = "mStateMachines";
            this.mStateMachines.Size = new System.Drawing.Size(164, 394);
            this.mStateMachines.TabIndex = 0;
            this.mStateMachines.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyDown);
            // 
            // mStateMachinesLabel
            // 
            this.mStateMachinesLabel.AutoSize = true;
            this.mStateMachinesLabel.Location = new System.Drawing.Point(-1, 8);
            this.mStateMachinesLabel.Name = "mStateMachinesLabel";
            this.mStateMachinesLabel.Size = new System.Drawing.Size(81, 13);
            this.mStateMachinesLabel.TabIndex = 1;
            this.mStateMachinesLabel.Text = "State Machines";
            // 
            // mAddStateMachineButton
            // 
            this.mAddStateMachineButton.Location = new System.Drawing.Point(2, 424);
            this.mAddStateMachineButton.Name = "mAddStateMachineButton";
            this.mAddStateMachineButton.Size = new System.Drawing.Size(51, 23);
            this.mAddStateMachineButton.TabIndex = 2;
            this.mAddStateMachineButton.Text = "Add";
            this.mAddStateMachineButton.UseVisualStyleBackColor = true;
            this.mAddStateMachineButton.Click += new System.EventHandler(this.AddStateMachineButtonClicked);
            this.mAddStateMachineButton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyDown);
            // 
            // mDeleteStateMachineButton
            // 
            this.mDeleteStateMachineButton.Location = new System.Drawing.Point(115, 424);
            this.mDeleteStateMachineButton.Name = "mDeleteStateMachineButton";
            this.mDeleteStateMachineButton.Size = new System.Drawing.Size(51, 23);
            this.mDeleteStateMachineButton.TabIndex = 3;
            this.mDeleteStateMachineButton.Text = "Del";
            this.mDeleteStateMachineButton.UseVisualStyleBackColor = true;
            this.mDeleteStateMachineButton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyDown);
            // 
            // mDeleteStateButton
            // 
            this.mDeleteStateButton.Location = new System.Drawing.Point(294, 424);
            this.mDeleteStateButton.Name = "mDeleteStateButton";
            this.mDeleteStateButton.Size = new System.Drawing.Size(51, 23);
            this.mDeleteStateButton.TabIndex = 7;
            this.mDeleteStateButton.Text = "Del";
            this.mDeleteStateButton.UseVisualStyleBackColor = true;
            this.mDeleteStateButton.Click += new System.EventHandler(this.AddStateButtonClicked);
            // 
            // mAddStateButton
            // 
            this.mAddStateButton.Location = new System.Drawing.Point(181, 424);
            this.mAddStateButton.Name = "mAddStateButton";
            this.mAddStateButton.Size = new System.Drawing.Size(51, 23);
            this.mAddStateButton.TabIndex = 6;
            this.mAddStateButton.Text = "Add";
            this.mAddStateButton.UseVisualStyleBackColor = true;
            this.mAddStateButton.Click += new System.EventHandler(this.AddStateButtonClicked);
            // 
            // mStatesLabel
            // 
            this.mStatesLabel.AutoSize = true;
            this.mStatesLabel.Location = new System.Drawing.Point(178, 8);
            this.mStatesLabel.Name = "mStatesLabel";
            this.mStatesLabel.Size = new System.Drawing.Size(37, 13);
            this.mStatesLabel.TabIndex = 5;
            this.mStatesLabel.Text = "States";
            // 
            // mStates
            // 
            this.mStates.FormattingEnabled = true;
            this.mStates.Location = new System.Drawing.Point(181, 24);
            this.mStates.Name = "mStates";
            this.mStates.Size = new System.Drawing.Size(164, 394);
            this.mStates.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.mDeleteStateButton);
            this.Controls.Add(this.mAddStateButton);
            this.Controls.Add(this.mStatesLabel);
            this.Controls.Add(this.mStates);
            this.Controls.Add(this.mDeleteStateMachineButton);
            this.Controls.Add(this.mAddStateMachineButton);
            this.Controls.Add(this.mStateMachinesLabel);
            this.Controls.Add(this.mStateMachines);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.OnLoad);
            this.SizeChanged += new System.EventHandler(this.OnSizeChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnKeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox mStateMachines;
        private System.Windows.Forms.Label mStateMachinesLabel;
        private System.Windows.Forms.Button mAddStateMachineButton;
        private System.Windows.Forms.Button mDeleteStateMachineButton;
        private System.Windows.Forms.Button mDeleteStateButton;
        private System.Windows.Forms.Button mAddStateButton;
        private System.Windows.Forms.Label mStatesLabel;
        private System.Windows.Forms.ListBox mStates;
    }
}

