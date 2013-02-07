/*
	BlamLib: .NET SDK for the Blam Engine

	See license\BlamLib\BlamLib for specific license information
*/
﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace BlamLib.Test
{
	[TestClass]
	public partial class HaloReach : BaseTestClass
	{
		[ClassInitialize]
		public static void Initialize(TestContext context)
		{
			(Program.GetManager(BlamVersion.HaloReach_Beta) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.HaloReach_Beta);
			(Program.GetManager(BlamVersion.HaloReach_Xbox) as Managers.IStringIdController)
				.StringIdCacheOpen(BlamVersion.HaloReach_Xbox);

			Directory.CreateDirectory(kTestResultsPath);
		}
		[ClassCleanup]
		public static void Dispose()
		{
			(Program.GetManager(BlamVersion.HaloReach_Beta) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.HaloReach_Beta);
			(Program.GetManager(BlamVersion.HaloReach_Xbox) as Managers.IStringIdController)
				.StringIdCacheClose(BlamVersion.HaloReach_Xbox);
		}

		static bool MapNeedsUniqueName(string header_name)
		{
			switch (header_name)
			{
				// dlc_defiant
				case "condemned":
				case "ff_unearthed":
				case "trainingpreserve":
					return true;
				default: return false;
			}
		}
		static readonly string[] kMapNames_Retail = {
			// 11860.10.07.24.0147
			@"Retail\maps\20_sword_slayer.map",
			@"Retail\maps\30_settlement.map",
			@"Retail\maps\35_island.map",
			@"Retail\maps\45_aftship.map",
			@"Retail\maps\45_launch_station.map",
			@"Retail\maps\50_panopticon.map",
			@"Retail\maps\52_ivory_tower.map",
			@"Retail\maps\70_boneyard.map",

			@"Retail\maps\ff10_prototype.map",
			@"Retail\maps\ff20_courtyard.map",
			@"Retail\maps\ff30_waterfront.map",
			@"Retail\maps\ff45_corvette.map",
			@"Retail\maps\ff50_park.map",
			@"Retail\maps\ff60_airview.map",
			@"Retail\maps\ff60_icecave.map",
			@"Retail\maps\ff70_holdout.map",

			@"Retail\maps\forge_halo.map",

			@"Retail\maps\m05.map",
			@"Retail\maps\m10.map",
			@"Retail\maps\m20.map",
			@"Retail\maps\m30.map",
			@"Retail\maps\m35.map",
			@"Retail\maps\m45.map",
			@"Retail\maps\m50.map",
			@"Retail\maps\m52.map",
			@"Retail\maps\m60.map",
			@"Retail\maps\m70.map",
			@"Retail\maps\m70_a.map",
			@"Retail\maps\m70_bonus.map",

			@"Retail\maps\mainmenu.map",

			// dlc_noble
			@"Retail\dlc_noble\dlc_invasion.map",
			@"Retail\dlc_noble\dlc_medium.map",
			@"Retail\dlc_noble\dlc_slayer.map",

			// dlc_defiant
			@"Retail\dlc_defiant\p1\condemned.map",
			@"Retail\dlc_defiant\p1\ff_unearthed.map",
			@"Retail\dlc_defiant\p1\trainingpreserve.map",
			@"Retail\dlc_defiant\condemned.map",
			@"Retail\dlc_defiant\ff_unearthed.map",
			@"Retail\dlc_defiant\trainingpreserve.map",
		};
		static readonly string[] kMapNames_Beta = {
			// 09449.10.03.25.1545
			@"Beta\maps\20_sword_slayer.map",
			@"Beta\maps\30_settlement.map",
			@"Beta\maps\70_boneyard.map",
			@"Beta\maps\ff10_prototype.map",
			@"Beta\maps\mainmenu.map",
		};
		static readonly string[] kMapNames_Delta = {
			// 09730.10.04.09.1309
			@"Delta\maps\20_sword_slayer.map",
			@"Delta\maps\30_settlement.map",
			@"Delta\maps\70_boneyard.map",
			@"Delta\maps\ff10_prototype.map",
			@"Delta\maps\mainmenu.map",
		};

		#region CacheOutputInformation
		static void CacheOutputInformationMethod(object param)
		{
			var args = param as CacheFileOutputInfoArgs;

			using(var handler = new CacheHandler<Blam.HaloReach.CacheFile>(args.Game, args.MapPath))
			{
				handler.Read();
				var cache = handler.CacheInterface;

				string header_name = cache.Header.Name;
				if (MapNeedsUniqueName(header_name))
					header_name = cache.GetUniqueName();

				Blam.CacheFile.OutputStringIds(cache,
					BuildResultPath(kTestResultsPath, args.Game, header_name, "string_ids", "txt"), true);
				Blam.CacheFile.OutputTags(cache,
					BuildResultPath(kTestResultsPath, args.Game, header_name, null, "txt"));
			}

			args.SignalFinished();
		}
		[TestMethod]
		public void HaloReachTestCacheOutputXbox()
		{
			CacheFileOutputInfoArgs.TestMethodThreaded(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.HaloReach_Xbox, kDirectoryXbox, kMapNames_Retail);
		}
		[TestMethod]
		public void HaloReachTestCacheOutputXboxBeta()
		{
			CacheFileOutputInfoArgs.TestMethodThreaded(TestContext,
				CacheOutputInformationMethod,
				BlamVersion.HaloReach_Beta, kDirectoryXbox, kMapNames_Delta);
		}
		#endregion


		class ScenarioScriptInterop : ScenarioScriptInteropGen3
		{
			TagInterface.Block<Blam.HaloReach.Tags.hs_scripts_block> hs_scripts;

			public ScenarioScriptInterop(Blam.HaloReach.CacheFile cf) : base(cf,
				new TagInterface.Block<Blam.HaloReach.Tags.hs_scripts_block>(null, 0),
				0x430,
				0x444, 0x450,
				0x518)
			{
				hs_scripts = base.sncr_hs_scripts as TagInterface.Block<Blam.HaloReach.Tags.hs_scripts_block>;
			}
		};

		// names: 104\8
		// bipd: 128\78
		// vehi: 140\D0
		// weap: 170\D0
		// eqip: 158\B4
		// term: 1AC\7C
		// scen: 110\DC
		// mach: 194\E4
		// ctrl: 1C4\DC
		// sscn: 1DC\8C
		// bloc: 614\D8
		// crea: 654\58
		// gint: 1F4\88
		// efsc: 20C\B0

		#region DumpScriptGraphs
		static void CacheDumpScriptGraphs(object param)
		{
			var args = param as CacheFileOutputInfoArgs;

			using (var handler = new CacheHandler<Blam.HaloReach.CacheFile>(args.Game, args.MapPath))
			{
				handler.Read();
				var cache = handler.CacheInterface;

				var filename = System.IO.Path.Combine(kTestResultsPath, cache.Header.Name + ".script_graph.txt");
				using(var sw = new StreamWriter(filename))
				{
					var interop = new ScenarioScriptInterop(cache);
					interop.DumpScriptGraphs(cache, sw);
				}
			}

			args.SignalFinished();
		}

		[TestMethod]
		public void HaloReachTestDumpScriptGraphs()
		{
			CacheFileOutputInfoArgs.TestMethodThreaded(TestContext,
				CacheDumpScriptGraphs,
				BlamVersion.HaloReach_Xbox, kDirectoryXbox, kMapNames_Retail);
		}
		#endregion

		#region ScanForScriptFunctions
		static void ScanForScriptFunctionsImpl(string[] script_functions, Blam.HaloReach.CacheFile cf)
		{
			var interop = new ScenarioScriptInterop(cf);

			interop.FindFunctionNames(script_functions);
		}
		static void ScanForScriptFunctions(BlamVersion engine, string path, string[] script_functions)
		{
			using (var handler = new CacheHandler<Blam.HaloReach.CacheFile>(engine, path))
			{
				var cf = handler.CacheInterface;
				cf.Read();

				ScanForScriptFunctionsImpl(script_functions, handler.CacheInterface);
			}
		}
		
		[TestMethod]
		public void HaloReachTestScanForScriptFunctions()
		{
			string[] script_functions;
			var engine = BlamVersion.HaloReach_Xbox;

			Scripts.InitializeScriptFunctionsList(engine, out script_functions);
			foreach (var s in kMapNames_Retail)
				ScanForScriptFunctions(engine, kDirectoryXbox + s, script_functions);
			Scripts.OutputFunctionNames(false, kTestResultsPath, "halo_reach.functions.xml", script_functions);
		}
		#endregion
	};
}