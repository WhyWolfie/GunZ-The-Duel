using Launcher.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Net;
using System.Net.Cache;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Launcher
{
	public class MainForm : Form
	{
		private delegate void AddLblD(Panel Parent, string name, Point P, Size S);

		private delegate void AddPBD(Panel Parent, string name, Point P, Size S);

		private delegate void SetValueD2(ProgressBar Bar, int value);

		private delegate void SetMaxD2(ProgressBar Bar, int value);

		private delegate void SetValueD(WolfProgressBar Bar, int value);

		private delegate void SetTextD(Control C, string text);

		private delegate void StatusD(string S);

		private const int threadcount = 6;

		private int threadDelay = 0;

		public string PatchName = "Patch.DG";

		public string GameFileName = "Gunz.exe";

		public string URL = "http://www.gunzupdater.com/DGLive/";

		public string News = "http://www.gunzupdater.com/DGlivenews.txt";

		private bool CanStart = false;

		private bool SelfPatch = false;

		public string LauncherName;

		private Thread NewsT;

		private Thread PatchT;

		private Thread MainCompareT;

		private List<Thread> CompareThreads;

		private string[] Files;

		private string[] Hashes;

		private string[] Sizes;

		private string[] CRCs;

		private List<int> ToDownload = new List<int>();

		private bool patchreceived = false;

		private DateTime LastUpdate = default(DateTime);

		private bool compareBusy = false;

		private int currentCompareLength = 0;

		private int lastCompareLength = 0;

		private Point P = new Point(0, 0);

		private bool dragging = false;

		private bool forwards = true;

		private int exitcount = 0;

		private long lastbytesrecved = 0L;

		private DateTime LastSpeedCheck = DateTime.Now;

		private long speed = 0L;

		private IContainer components = null;

		private WolfProgressBar PB;

		private PictureBox BtnStart;

		private Label LblVersion;

		private Label LblLastUpdate;

		private PictureBox BtnMin;

		private PictureBox BtnClose;

		private System.Windows.Forms.Timer TmrPBTest;

		private Label LblNewsDate;

		private Label LblNews;

		private System.Windows.Forms.Timer TmrPatch;

		private System.Windows.Forms.Timer TmrExit;

		private Label label1;

		private ContextMenuStrip MenuSettings;

		private ToolStripMenuItem gunZToolStripMenuItem;

		private ToolStripMenuItem launcherToolStripMenuItem;

		private Panel panel1;

		public MainForm()
		{
			try
			{
				InitializeComponent();
			}
			catch (Exception e)
			{
				DG.Log("MainForm::MainForm", e);
			}
			Init();
		}

		private void Init()
		{
			try
			{
				Status("Intializing launcher");
				string processName = Process.GetCurrentProcess().ProcessName;
				if (processName == "Launcher.vshost")
				{
					panel1.Visible = true;
				}
				LauncherName = Path.GetFileName(Application.ExecutablePath);
				NewsT = new Thread(NewsThread);
				NewsT.IsBackground = true;
				NewsT.Priority = ThreadPriority.Highest;
				PatchT = new Thread(PatchThread);
				PatchT.IsBackground = true;
				PatchT.Priority = ThreadPriority.Highest;
				PatchT.Start();
				NewsT.Start();
				MainCompareT = new Thread(MainCompareThread);
				MainCompareT.IsBackground = true;
				MainCompareT.Start();
				Status("DarKGunZ Launcher started.  Downloading data.");
			}
			catch (Exception e)
			{
				DG.Log("Init()", e);
			}
		}

		private void MainCompareThread()
		{
			while (!patchreceived)
			{
				Thread.Sleep(10);
			}
			Status("Patch file downloaded.  Processing data.");
			long num = 0L;
			string[] sizes = Sizes;
			foreach (string s in sizes)
			{
				num += int.Parse(s);
			}
			int num2 = Files.Length % 6 - 1;
			int num3 = Files.Length / 6;
			List<string> list = new List<string>();
			List<int> list2 = new List<int>();
			List<string> list3 = new List<string>();
			List<string> list4 = new List<string>();
			CompareThreads = new List<Thread>();
			List<object> list5 = new List<object>();
			for (int j = 0; j < Files.Length; j++)
			{
				if (Files.Length - j == num2)
				{
					int num4 = 1;
					while (j < Files.Length)
					{
						if (num4 == list5.Count)
						{
							num4 = 1;
						}
						((List<string>)((object[])list5[num4])[0]).Add(Files[j]);
						((List<int>)((object[])list5[num4])[1]).Add(int.Parse(Sizes[j]));
						((List<string>)((object[])list5[num4])[2]).Add(CRCs[j]);
						((List<string>)((object[])list5[num4])[3]).Add(Hashes[j]);
						j++;
						num4++;
					}
				}
				else
				{
					list.Add(Files[j]);
					list2.Add(int.Parse(Sizes[j]));
					list3.Add(CRCs[j]);
					list4.Add(Hashes[j]);
				}
				if (j != 0 && j % num3 == 0)
				{
					object item = new object[4]
					{
						new List<string>(list),
						new List<int>(list2),
						new List<string>(list3),
						new List<string>(list4)
					};
					list5.Add(item);
					list.Clear();
					list2.Clear();
					list3.Clear();
					list4.Clear();
				}
				if (j == Files.Length - 1 && list5.Count == 0)
				{
					object item = new object[4]
					{
						new List<string>(list),
						new List<int>(list2),
						new List<string>(list3),
						new List<string>(list4)
					};
					list5.Add(item);
				}
			}
			int num5 = 0;
			for (int j = 0; j < list5.Count; j++)
			{
				num5 += ((List<string>)((object[])list5[j])[0]).Count;
			}
			if (num5 != Files.Length)
			{
				if (list.Count > 0)
				{
					object item = new object[4]
					{
						new List<string>(list),
						new List<int>(list2),
						new List<string>(list3),
						new List<string>(list4)
					};
					list5.Add(item);
				}
				num5 = 0;
				for (int j = 0; j < list5.Count; j++)
				{
					num5 += ((List<string>)((object[])list5[j])[0]).Count;
				}
			}
			if (num5 != Files.Length)
			{
				int num6 = -1;
				int num7 = -1;
				try
				{
					num6 = ((List<string>)((object[])list5[0])[0]).Count;
					num7 = ((List<string>)((object[])list5[1])[0]).Count;
				}
				catch
				{
				}
				MessageBox.Show("Count mismatch in MainCompareThread.  Notify Wo1f." + Environment.NewLine + "FC: " + num5 + " - RC: " + Files.Length + " - R: " + num2 + " - RA:" + list5.Count + " - RA[0][0] " + num6 + " - RA[1][0] " + num7, "Error");
			}
			bool visible = panel1.Visible;
			Status("Beginning file comparison.");
			for (int j = 0; j < list5.Count; j++)
			{
				if (visible)
				{
					Point p = new Point(30, 2 + j * 16);
					Point p2 = new Point(1, 2 + j * 16);
					Size s2 = new Size(25, 13);
					Size s3 = new Size(panel1.Width - 40, 14);
					AddLbl(panel1, "Lbl" + j, p2, s2);
					AddPB(panel1, "PB" + j, p, s3);
				}
				object[] parameter = (object[])list5[j];
				Thread thread = new Thread(CompareThread);
				thread.Name = j.ToString();
				thread.IsBackground = true;
				thread.Start(parameter);
				Thread.Sleep(13);
			}
			DateTime now = DateTime.Now;
			bool flag = true;
			while (true)
			{
				if (!flag)
				{
					return;
				}
				SetValue(PB, currentCompareLength / 1024);
				SetMax(PB, (int)num / 1024);
				if (DateTime.Now.Subtract(now).TotalMilliseconds >= 495.0)
				{
					int num8 = currentCompareLength - lastCompareLength;
					num8 *= 2;
					Status($"Comparing {DG.ShortenBytes(currentCompareLength)} of {DG.ShortenBytes(num)} at {DG.ShortenBytes(num8)}/s");
					SetValue(PB, currentCompareLength / 1024);
					SetMax(PB, (int)num / 1024);
					lastCompareLength = currentCompareLength;
					now = DateTime.Now;
					if (currentCompareLength == num)
					{
						break;
					}
				}
				Thread.Sleep(10);
			}
			Status("Preparing downloads...");
			if (ToDownload.Count == 0)
			{
				BtnStart.BackgroundImage = Resources.Playnormal;
				CanStart = true;
				Status("Ready to play!");
				return;
			}
			SetMax(PB, 100);
			SetValue(PB, 0);
			Process[] processesByName = Process.GetProcessesByName("gunz");
			if (processesByName.Length != 0)
			{
				DialogResult dialogResult = MessageBox.Show("You are currently playing DarK GunZ and cannot patch correctly while it is running.  Would you like to close the game and continue with patching?  Yes will close all instances of the game.  No will close the launcher.", "Notice", MessageBoxButtons.YesNo, MessageBoxIcon.Asterisk);
				if (dialogResult == DialogResult.Yes)
				{
					Process[] array = processesByName;
					foreach (Process process in array)
					{
						process.Kill();
					}
				}
				else
				{
					Exit();
				}
			}
			DownloadFile();
		}

		private void AddLbl(Panel Parent, string name, Point P, Size S)
		{
			if (Parent.InvokeRequired)
			{
				Parent.Invoke(new AddLblD(AddLbl), Parent, name, P, S);
				return;
			}
			Label label = new Label();
			label.Name = name;
			label.Parent = Parent;
			Parent.Controls.Add(label);
			label.Location = P;
			label.Size = S;
			label.BringToFront();
			label.BackColor = Color.Transparent;
		}

		private void AddPB(Panel Parent, string name, Point P, Size S)
		{
			if (Parent.InvokeRequired)
			{
				Parent.Invoke(new AddPBD(AddPB), Parent, name, P, S);
				return;
			}
			ProgressBar progressBar = new ProgressBar();
			progressBar.Name = name;
			progressBar.Parent = Parent;
			Parent.Controls.Add(progressBar);
			progressBar.Location = P;
			progressBar.Size = S;
		}

		private void SetValue(ProgressBar Bar, int value)
		{
			if (Bar.InvokeRequired)
			{
				Bar.Invoke(new SetValueD2(SetValue), Bar, value);
			}
			else
			{
				Bar.Value = value;
			}
		}

		private void SetMax(ProgressBar Bar, int value)
		{
			if (Bar.InvokeRequired)
			{
				Bar.Invoke(new SetValueD2(SetMax), Bar, value);
			}
			else
			{
				Bar.Maximum = value;
			}
		}

		private void SetValue(WolfProgressBar Bar, int value)
		{
			if (Bar.InvokeRequired)
			{
				Bar.Invoke(new SetValueD(SetValue), Bar, value);
			}
			else
			{
				Bar.Value = value;
			}
		}

		private void SetMax(WolfProgressBar Bar, int value)
		{
			if (Bar.InvokeRequired)
			{
				Bar.Invoke(new SetValueD(SetMax), Bar, value);
			}
			else
			{
				Bar.Maximum = value;
			}
		}

		private void CompareThread(object arg)
		{
			object[] array = (object[])arg;
			List<string> list = (List<string>)array[0];
			List<int> list2 = (List<int>)array[1];
			List<string> list3 = (List<string>)array[2];
			List<string> list4 = (List<string>)array[3];
			int num = 0;
			int num2 = int.Parse(Thread.CurrentThread.Name);
			bool flag = panel1.Visible;
			ProgressBar bar = null;
			Label c = null;
			try
			{
				bar = (ProgressBar)base.Controls.Find("PB" + num2, searchAllChildren: true)[0];
				c = (Label)base.Controls.Find("Lbl" + num2, searchAllChildren: true)[0];
			}
			catch
			{
				flag = false;
			}
			if (flag)
			{
				SetMax(bar, list.Count - 1);
			}
			for (int i = 0; i < list.Count; i++)
			{
				if (flag)
				{
					SetText(c, i.ToString());
					SetValue(bar, i);
				}
				bool flag2 = false;
				string fileName = list[i];
				FileInfo fileInfo = new FileInfo(fileName);
				int num3 = list2[i];
				string text = list3[i];
				string text2 = list4[i];
				if (!fileInfo.Exists)
				{
					flag2 = true;
					while (compareBusy)
					{
						Thread.Sleep(3);
					}
					compareBusy = true;
					currentCompareLength += num3;
					compareBusy = false;
				}
				else if (num3 != fileInfo.Length)
				{
					flag2 = true;
					while (compareBusy)
					{
						Thread.Sleep(3);
					}
					compareBusy = true;
					currentCompareLength += num3;
					compareBusy = false;
				}
				else
				{
					byte[] array2 = File.ReadAllBytes(fileInfo.FullName);
					string value = Hashoil.Hash(Encoding.ASCII.GetString(array2));
					if (!text2.Equals(value))
					{
						flag2 = true;
					}
					while (compareBusy)
					{
						Thread.Sleep(3);
					}
					compareBusy = true;
					currentCompareLength += array2.Length;
					compareBusy = false;
				}
				if (!flag2)
				{
					continue;
				}
				bool flag3 = false;
				string text3 = fileInfo.FullName.Replace(Application.StartupPath + "\\", "").Replace("\\", "/").ToLower()
					.Trim();
				for (int j = 0; j < Files.Length; j++)
				{
					if (Files[j].ToLower() == text3)
					{
						ToDownload.Add(j);
						flag3 = true;
						break;
					}
				}
				if (!flag3)
				{
					DG.Log("Failed to add file '" + text3 + "' to the download list.");
				}
			}
		}

		private void PatchThread()
		{
			try
			{
				WebClient webClient = new WebClient();
				string text = webClient.DownloadString(URL + PatchName);
				if (text.Trim() == "")
				{
					MessageBox.Show("Could not download patch file.  Contact DarKGunZ Administrators for help.", "Error");
				}
				string text2 = "";
				string text3 = text;
				try
				{
					string s = DG.FindInstancesOf(text3, "Date")[0];
					LastUpdate = DateTime.Parse(s);
					string str = "";
					int num = (int)DateTime.Now.Subtract(LastUpdate).TotalDays;
					if (num == 1)
					{
						str = "Yesterday";
					}
					else if (num == 0)
					{
						str = "Today";
					}
					else if (num > 1)
					{
						str = num + " days ago";
					}
					SetText(LblLastUpdate, "Last update was " + str);
				}
				catch (Exception e)
				{
					DG.Log("PatchThread3", e);
				}
				Files = DG.FindInstancesOf(text3, "Names");
				Sizes = DG.FindInstancesOf(text3, "Sizes");
				Hashes = DG.FindInstancesOf(text3, "Hashes");
				CRCs = DG.FindInstancesOf(text3, "CRCs");
				if (Files.Length != Sizes.Length || Files.Length != Hashes.Length || Files.Length != CRCs.Length)
				{
					MessageBox.Show("Value count mismatch - Patch file is likely corrupted", "Error");
				}
				else
				{
					Status("Preparing files");
					try
					{
						string[] files = Files;
						foreach (string fileName in files)
						{
							FileInfo fileInfo = new FileInfo(fileName);
							if (!fileInfo.Directory.Exists)
							{
								fileInfo.Directory.Create();
								Thread.Sleep(100);
							}
						}
					}
					catch (Exception e)
					{
						DG.Log("PatchThread::Preparing Files", e);
					}
					Status("Comparing files");
					patchreceived = true;
				}
			}
			catch (WebException ex)
			{
				string text4 = "";
				if (ex.Status == WebExceptionStatus.ProtocolError)
				{
					WebResponse response = ex.Response;
					using (StreamReader streamReader = new StreamReader(response.GetResponseStream()))
					{
						text4 = streamReader.ReadToEnd();
					}
				}
				DG.Log("PatchThread::WebException", ex);
				TmrExit.Start();
				MessageBox.Show("Unable to download patch file in PT due to Protocol Error " + ex.Message, "Error");
			}
			catch (Exception e)
			{
				DG.Log("PatchThread2", e);
				TmrExit.Start();
				MessageBox.Show("Unable to download patch file in PT()", "Error");
			}
		}

		private void NewsThread()
		{
			try
			{
				Thread.Sleep(500);
				WebClient webClient = new WebClient();
				webClient.CachePolicy = new RequestCachePolicy(RequestCacheLevel.BypassCache);
				string text = webClient.DownloadString(News);
				string[] array = text.Split('\n');
				string str = array[0];
				string text2 = array[1];
				text = "";
				for (int i = 2; i < array.Length; i++)
				{
					text = text + array[i].Trim() + Environment.NewLine;
				}
				SetText(LblVersion, "Game Version: " + str);
				SetText(LblNewsDate, text2);
				SetText(LblNews, text);
			}
			catch
			{
				SetText(LblNews, "Unable to download News text");
			}
		}

		private void SetText(Control C, string text)
		{
			if (C.InvokeRequired)
			{
				C.Invoke(new SetTextD(SetText), C, text);
			}
			else
			{
				C.Text = text;
			}
		}

		private void Status(string S)
		{
			if (PB.InvokeRequired)
			{
				PB.Invoke(new StatusD(Status), S);
				return;
			}
			if (S == "Ready to play!")
			{
				PB.Value = PB.Maximum;
			}
			PB.Text = S;
		}

		private void Exit()
		{
			Program.Exit();
		}

		private void aMouseDown(object sender, MouseEventArgs e)
		{
			P = Cursor.Position;
			dragging = true;
		}

		private void aMouseMove(object sender, MouseEventArgs e)
		{
			if (dragging)
			{
				int num = Cursor.Position.X - P.X;
				int num2 = Cursor.Position.Y - P.Y;
				P = Cursor.Position;
				base.Location = new Point(base.Location.X + num, base.Location.Y + num2);
			}
		}

		private void aMouseUp(object sender, MouseEventArgs e)
		{
			dragging = false;
		}

		private void BtnStart_MouseEnter(object sender, EventArgs e)
		{
			if (CanStart)
			{
				BtnStart.BackgroundImage = Resources.Playhover;
			}
		}

		private void BtnStart_MouseLeave(object sender, EventArgs e)
		{
			if (CanStart)
			{
				BtnStart.BackgroundImage = Resources.Playnormal;
			}
		}

		private void BtnClose_MouseEnter(object sender, EventArgs e)
		{
			BtnClose.BackgroundImage = Resources.Closehover;
		}

		private void BtnClose_MouseLeave(object sender, EventArgs e)
		{
			BtnClose.BackgroundImage = Resources.Closenormal;
		}

		private void BtnMin_MouseEnter(object sender, EventArgs e)
		{
			BtnMin.BackgroundImage = Resources.minhover;
		}

		private void BtnMin_MouseLeave(object sender, EventArgs e)
		{
			BtnMin.BackgroundImage = Resources.minnormal;
		}

		private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			Exit();
		}

		private void BtnClose_Click(object sender, EventArgs e)
		{
			Exit();
		}

		private void BtnMin_Click(object sender, EventArgs e)
		{
			base.WindowState = FormWindowState.Minimized;
		}

		private void TmrPBTest_Tick(object sender, EventArgs e)
		{
			if (forwards)
			{
				PB.Value++;
			}
			else
			{
				PB.Value--;
			}
			if (PB.Value == 0)
			{
				forwards = true;
			}
			if (PB.Value == 100)
			{
				forwards = false;
			}
			PB.Text = "Update test: " + PB.Value + "/" + PB.Maximum + " (" + PB.Value * 100 / PB.Maximum + "%)";
		}

		private void BtnStart_Click(object sender, EventArgs e)
		{
			if (CanStart)
			{
				FileInfo fileInfo = new FileInfo(GameFileName);
				if (!fileInfo.Exists)
				{
					MessageBox.Show(GameFileName + " not found.");
					TmrExit.Start();
				}
				else
				{
					SerialKey.Create();
					Process.Start(GameFileName);
					TmrExit.Start();
				}
			}
		}

		private void TmrExit_Tick(object sender, EventArgs e)
		{
			try
			{
				if (exitcount == 5)
				{
					Exit();
				}
				SetMax(PB, 5);
				SetValue(PB, exitcount);
				exitcount++;
				Status("Exiting in " + (PB.Maximum - PB.Value) + " seconds.");
			}
			catch
			{
				Exit();
			}
		}

		private void wc_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
		{
			try
			{
				int value = (int)(e.BytesReceived / 1024);
				int maximum = (int)(e.TotalBytesToReceive / 1024);
				PB.Maximum = maximum;
				PB.Value = value;
				if (DateTime.Now.Subtract(LastSpeedCheck).TotalMilliseconds >= 250.0)
				{
					speed = e.BytesReceived - lastbytesrecved;
					speed *= 4L;
					lastbytesrecved = e.BytesReceived;
					LastSpeedCheck = DateTime.Now;
				}
				string s = $"Downloading file '{e.UserState}' ({DG.ShortenBytes(e.BytesReceived)} / {DG.ShortenBytes(e.TotalBytesToReceive)}) {e.ProgressPercentage}% at {DG.ShortenBytes(speed)}/s";
				Status(s);
			}
			catch (Exception e2)
			{
				DG.Log("WebClient DownloadProgressChanged", e2);
			}
		}

		private void wc_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
		{
			Status("Completed downloading file " + e.UserState);
			LastSpeedCheck = DateTime.Now;
			lastbytesrecved = 0L;
			if (e.UserState.ToString().ToLower().Equals(LauncherName.ToLower() + "_"))
			{
				int num = 0;
				string text = "";
				text = ((num != 0) ? ("SelfPatch" + num + ".exe") : "SelfPatch.exe");
				while (true)
				{
					try
					{
						if (File.Exists(text))
						{
							File.Delete(text);
						}
					}
					catch (Exception ex)
					{
						DG.Log("Minor exception in wc_downloadFileCompleted.  Retry #" + num + ".  Msg: " + ex.Message);
						num++;
						continue;
					}
					break;
				}
				File.WriteAllBytes(text, Resources.SelfPatch);
				FileInfo fileInfo = new FileInfo(text);
				int id = Process.GetCurrentProcess().Id;
				string arg = e.UserState.ToString();
				string launcherName = LauncherName;
				string arguments = $"PID=\"{id}\"; New=\"{arg}\"; Old=\"{launcherName}\";";
				if (!Process.GetCurrentProcess().ProcessName.Contains("vshost"))
				{
					Process.Start(text, arguments);
				}
				else
				{
					MessageBox.Show("SelfPatch() did not execute due to Visual Studio Environment");
				}
			}
			DownloadFile();
		}

		private void DownloadFile()
		{
			if (ToDownload.Count == 0)
			{
				BtnStart.BackgroundImage = Resources.Playnormal;
				CanStart = true;
				Status("Ready to play!");
				return;
			}
			WebClient webClient = new WebClient();
			webClient.DownloadProgressChanged += wc_DownloadProgressChanged;
			webClient.DownloadFileCompleted += wc_DownloadFileCompleted;
			string text = Files[ToDownload[0]];
			FileInfo fileInfo = new FileInfo(text);
			if (fileInfo.Exists)
			{
				try
				{
					fileInfo.Delete();
				}
				catch (Exception e)
				{
					DG.Log("DownloadFile::FI.Exists", e);
				}
			}
			lastbytesrecved = 0L;
			LastSpeedCheck = DateTime.Now;
			if (text.ToLower().Equals(LauncherName.ToLower()))
			{
				SelfPatch = true;
				webClient.DownloadFileAsync(new Uri(URL + text), text + "_", text + "_");
			}
			else
			{
				webClient.DownloadFileAsync(new Uri(URL + text), text, text);
			}
			ToDownload.RemoveAt(0);
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && components != null)
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.BtnStart = new System.Windows.Forms.PictureBox();
            this.LblVersion = new System.Windows.Forms.Label();
            this.LblLastUpdate = new System.Windows.Forms.Label();
            this.BtnMin = new System.Windows.Forms.PictureBox();
            this.BtnClose = new System.Windows.Forms.PictureBox();
            this.TmrPBTest = new System.Windows.Forms.Timer(this.components);
            this.LblNewsDate = new System.Windows.Forms.Label();
            this.LblNews = new System.Windows.Forms.Label();
            this.TmrPatch = new System.Windows.Forms.Timer(this.components);
            this.TmrExit = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.MenuSettings = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.gunZToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.launcherToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.PB = new Launcher.WolfProgressBar();
            ((System.ComponentModel.ISupportInitialize)(this.BtnStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BtnMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BtnClose)).BeginInit();
            this.MenuSettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // BtnStart
            // 
            this.BtnStart.BackColor = System.Drawing.Color.Transparent;
            this.BtnStart.BackgroundImage = global::Launcher.Properties.Resources.Playdisabled;
            this.BtnStart.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnStart.Location = new System.Drawing.Point(460, 384);
            this.BtnStart.Name = "BtnStart";
            this.BtnStart.Size = new System.Drawing.Size(180, 77);
            this.BtnStart.TabIndex = 1;
            this.BtnStart.TabStop = false;
            this.BtnStart.Click += new System.EventHandler(this.BtnStart_Click);
            this.BtnStart.MouseEnter += new System.EventHandler(this.BtnStart_MouseEnter);
            this.BtnStart.MouseLeave += new System.EventHandler(this.BtnStart_MouseLeave);
            // 
            // LblVersion
            // 
            this.LblVersion.AutoSize = true;
            this.LblVersion.BackColor = System.Drawing.Color.Transparent;
            this.LblVersion.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblVersion.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(99)))), ((int)(((byte)(90)))), ((int)(((byte)(86)))));
            this.LblVersion.Location = new System.Drawing.Point(24, 409);
            this.LblVersion.Name = "LblVersion";
            this.LblVersion.Size = new System.Drawing.Size(119, 20);
            this.LblVersion.TabIndex = 2;
            this.LblVersion.Text = "Game Version: ";
            this.LblVersion.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.LblVersion.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.LblVersion.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            // 
            // LblLastUpdate
            // 
            this.LblLastUpdate.AutoSize = true;
            this.LblLastUpdate.BackColor = System.Drawing.Color.Transparent;
            this.LblLastUpdate.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblLastUpdate.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(57)))), ((int)(((byte)(53)))));
            this.LblLastUpdate.Location = new System.Drawing.Point(25, 429);
            this.LblLastUpdate.Name = "LblLastUpdate";
            this.LblLastUpdate.Size = new System.Drawing.Size(184, 18);
            this.LblLastUpdate.TabIndex = 4;
            this.LblLastUpdate.Text = "Last update was Yesterday";
            this.LblLastUpdate.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.LblLastUpdate.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.LblLastUpdate.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            // 
            // BtnMin
            // 
            this.BtnMin.BackColor = System.Drawing.Color.Transparent;
            this.BtnMin.BackgroundImage = global::Launcher.Properties.Resources.minnormal;
            this.BtnMin.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnMin.Location = new System.Drawing.Point(607, 9);
            this.BtnMin.Name = "BtnMin";
            this.BtnMin.Size = new System.Drawing.Size(15, 15);
            this.BtnMin.TabIndex = 5;
            this.BtnMin.TabStop = false;
            this.BtnMin.Click += new System.EventHandler(this.BtnMin_Click);
            this.BtnMin.MouseEnter += new System.EventHandler(this.BtnMin_MouseEnter);
            this.BtnMin.MouseLeave += new System.EventHandler(this.BtnMin_MouseLeave);
            // 
            // BtnClose
            // 
            this.BtnClose.BackColor = System.Drawing.Color.Transparent;
            this.BtnClose.BackgroundImage = global::Launcher.Properties.Resources.Closenormal;
            this.BtnClose.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.BtnClose.Location = new System.Drawing.Point(628, 9);
            this.BtnClose.Name = "BtnClose";
            this.BtnClose.Size = new System.Drawing.Size(15, 15);
            this.BtnClose.TabIndex = 6;
            this.BtnClose.TabStop = false;
            this.BtnClose.Click += new System.EventHandler(this.BtnClose_Click);
            this.BtnClose.MouseEnter += new System.EventHandler(this.BtnClose_MouseEnter);
            this.BtnClose.MouseLeave += new System.EventHandler(this.BtnClose_MouseLeave);
            // 
            // TmrPBTest
            // 
            this.TmrPBTest.Interval = 25;
            this.TmrPBTest.Tick += new System.EventHandler(this.TmrPBTest_Tick);
            // 
            // LblNewsDate
            // 
            this.LblNewsDate.AutoSize = true;
            this.LblNewsDate.BackColor = System.Drawing.Color.Transparent;
            this.LblNewsDate.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblNewsDate.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(73)))), ((int)(((byte)(68)))), ((int)(((byte)(62)))));
            this.LblNewsDate.Location = new System.Drawing.Point(493, 185);
            this.LblNewsDate.Name = "LblNewsDate";
            this.LblNewsDate.Size = new System.Drawing.Size(123, 16);
            this.LblNewsDate.TabIndex = 7;
            this.LblNewsDate.Text = "00.00.000, 00:00:00";
            this.LblNewsDate.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.LblNewsDate.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.LblNewsDate.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            // 
            // LblNews
            // 
            this.LblNews.BackColor = System.Drawing.Color.Transparent;
            this.LblNews.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LblNews.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(102)))), ((int)(((byte)(96)))), ((int)(((byte)(89)))));
            this.LblNews.Location = new System.Drawing.Point(232, 205);
            this.LblNews.Name = "LblNews";
            this.LblNews.Size = new System.Drawing.Size(389, 132);
            this.LblNews.TabIndex = 8;
            this.LblNews.Text = "News Text";
            this.LblNews.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.LblNews.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.LblNews.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.LblNews.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            // 
            // TmrPatch
            // 
            this.TmrPatch.Enabled = true;
            // 
            // TmrExit
            // 
            this.TmrExit.Interval = 1000;
            this.TmrExit.Tick += new System.EventHandler(this.TmrExit_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.ContextMenuStrip = this.MenuSettings;
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(99)))), ((int)(((byte)(90)))), ((int)(((byte)(86)))));
            this.label1.Location = new System.Drawing.Point(559, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "&Settings";
            this.label1.Visible = false;
            // 
            // MenuSettings
            // 
            this.MenuSettings.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.gunZToolStripMenuItem,
            this.launcherToolStripMenuItem});
            this.MenuSettings.Name = "MenuSettings";
            this.MenuSettings.Size = new System.Drawing.Size(124, 48);
            // 
            // gunZToolStripMenuItem
            // 
            this.gunZToolStripMenuItem.Name = "gunZToolStripMenuItem";
            this.gunZToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.gunZToolStripMenuItem.Text = "&GunZ";
            // 
            // launcherToolStripMenuItem
            // 
            this.launcherToolStripMenuItem.Name = "launcherToolStripMenuItem";
            this.launcherToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.launcherToolStripMenuItem.Text = "&Launcher";
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.ForeColor = System.Drawing.Color.Lime;
            this.panel1.Location = new System.Drawing.Point(235, 9);
            this.panel1.MaximumSize = new System.Drawing.Size(200, 1000);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 15);
            this.panel1.TabIndex = 10;
            this.panel1.Visible = false;
            // 
            // PB
            // 
            this.PB.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PB.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(124)))), ((int)(((byte)(116)))), ((int)(((byte)(106)))));
            this.PB.Location = new System.Drawing.Point(4, 340);
            this.PB.Maximum = 100;
            this.PB.Minimum = 0;
            this.PB.Name = "PB";
            this.PB.Size = new System.Drawing.Size(645, 24);
            this.PB.TabIndex = 0;
            this.PB.Text = "Downloading Patch File";
            this.PB.Value = 0;
            this.PB.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.PB.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.PB.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.BackgroundImage = global::Launcher.Properties.Resources.launcher;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(652, 482);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.LblNews);
            this.Controls.Add(this.LblNewsDate);
            this.Controls.Add(this.BtnClose);
            this.Controls.Add(this.BtnMin);
            this.Controls.Add(this.LblLastUpdate);
            this.Controls.Add(this.LblVersion);
            this.Controls.Add(this.BtnStart);
            this.Controls.Add(this.PB);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DarKGunZ Launcher";
            this.TransparencyKey = System.Drawing.Color.Magenta;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aMouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.aMouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aMouseUp);
            ((System.ComponentModel.ISupportInitialize)(this.BtnStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BtnMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BtnClose)).EndInit();
            this.MenuSettings.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

		}
	}
}
