cask "kicad-minimal" do
  version "5.1.12-1"
  sha256 "c7398a2f19e4f5d345c9678f81c36501a1f01d22044f289670cce6ccf744d25b"

  url "https://github.com/ohmtech-rdi/kicad-releases-mirror/releases/download/5.1.12-1/kicad-minimal-5.1.12-1-10_14.dmg",
      verified: "github.com/"
  name "KiCad"
  desc "Electronics design automation suite"
  homepage "https://kicad.org/"

  depends_on macos: ">= :mojave"

  app "KiCad/kicad.app",            target: "KiCad/kicad.app"
  app "KiCad/bitmap2component.app", target: "KiCad/bitmap2component.app"
  app "KiCad/eeschema.app",         target: "KiCad/eeschema.app"
  app "KiCad/gerbview.app",         target: "KiCad/gerbview.app"
  app "KiCad/pcb_calculator.app",   target: "KiCad/pcb_calculator.app"
  app "KiCad/pcbnew.app",           target: "KiCad/pcbnew.app"
  app "KiCad/pl_editor.app",        target: "KiCad/pl_editor.app"

  uninstall rmdir: [
    "/Library/Application Support/kicad",
    "#{appdir}/KiCad",
  ]

  zap trash: "~/Library/Preferences/kicad"
end
