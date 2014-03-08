using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;


/// <summary>
/// Outputs data
///jj </summary>
public class Coolpart : PartModule
{
	/// <summary>
	/// Raises the start event.
	/// </summary>
	/// <param name="state">State.</param>
	private Rect _windowPosition = new Rect();
	public override void OnStart(StartState state)
	{
		if (state != StartState.Editor)
			RenderingManager.AddToPostDrawQueue (0, onDraw);
 	}

	private void onDraw()
	{
		if (this.vessel == FlightGlobals.ActiveVessel)
			_windowPosition = GUILayout.Window (10, _windowPosition, OnWindow, "Cool title");
	}

	private void OnWindow(int windowId)
	{
		GUILayout.BeginHorizontal (GUILayout.Width (250f));
		GUILayout.Label ("This is a label");
		GUILayout.EndHorizontal ();

		GUI.DragWindow ();
	}
}
