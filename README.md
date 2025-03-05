# Universal-USD-Bridge-Multi-DCC-Synchronization-with-PyQt

Project Summary: Universal USD Bridge – Multi-DCC Synchronization
Overview
The Universal USD Bridge is a PyQt-based application that enables seamless interoperability between multiple Digital Content Creation (DCC) applications, allowing artists and technical directors to share a live USD file across different software in real-time.

This tool ensures that meshes, rigs, and animations remain synchronized, even when transferring assets between Maya, Houdini, Blender, Unreal Engine, and other DCCs. The application automatically detects installed DCCs, launches them, and manages USD data synchronization, making it easier for teams to collaborate across platforms.

Features
✅ Multi-DCC Detection & Launch – Scans environment variables to identify installed DCCs and provides a UI to open them from a single interface.
✅ Live USD File Sharing – Ensures that all connected DCCs are working from the same USD Stage, reducing the need for manual file imports/exports.
✅ Animation & Rig Synchronization – Automatically retargets animation across different software, compensating for differences in rig structure and constraints.
✅ Real-Time Scene Updates – Uses USD Stages & Layers to allow non-destructive editing, ensuring modifications in one DCC appear in others.
✅ Version Control & Collaboration – Integrates with Git/Perforce to manage USD revisions, ensuring project integrity.
✅ Intuitive PyQt-Based UI – Provides an easy-to-use interface for artists to choose active DCCs, sync settings, and monitor status.

Technology Stack
Programming Languages: Python (PyQt, USD API, subprocess, networking)
DCC APIs: Maya (cmds, OpenMaya), Houdini (Houdini Engine, USD LOPs), Blender (bpy), Unreal Engine (USD Stage API)
Rendering & Scene Management: USD Hydra, OpenGL
Networking & Communication: OSC/WebSockets for real-time cross-DCC updates
Data Handling: USD Stages, Layers, Variants, and Payloads
Version Control: Git, Perforce

